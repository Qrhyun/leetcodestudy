## 测压

在 Windows 11 + Visual Studio 环境下，你仍然可以按照“单机极限 → 稳定性 → 找 10 ms 延迟下的最大并发”三段式来做压测，只是工具链和步骤与 Linux 略有区别。下面给出一份**零依赖（全部用 Windows 自带或开源免费工具）**的实战清单，每一步都说明“为什么、怎么做、做完看什么”。

---

1. 调系统句柄和端口限制  
   • 为什么：Win11 默认进程句柄 16 k，TCP 动态端口 16 k，不先改大直接“炸”。  
   • 怎么做：

1) 管理员 PowerShell：
   ```powershell
   netsh int ipv4 set dynamicport tcp start=1024 num=64511
   reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows" /v GDIProcessHandleQuota /t REG_DWORD /d 50000 /f
   reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows" /v USERProcessHandleQuota /t REG_DWORD /d 50000 /f
   ```
2) 重启电脑生效。  
   • 做完得到：单机可开 5 w+ 句柄，动态端口 1024-65535 全覆盖。

---

2. 在 VS 里编译“Ping-Pong Server”  
   • 为什么：需要一个能跑在 IIS Express/Kestrel 的 IM 服务做靶子。  
   • 怎么做：

- .NET 6/7/8 控制台模板 → 加 WebSocket 或 TCP 端口 9000 → 代码逻辑：收到一条 64 B 的 Ping → 回一条 64 B 的 Pong。
- `dotnet run --urls http://localhost:9000` 即可。  
  • 做完得到：一个本机可访问的 IM 服务，用来被压。

---

3. 写“Ping-Pong Client”并用 VS 调试  
   • 为什么：现成的 ab/wrk 不支持私有协议，只能自己写。  
   • 怎么做：

- 新建 .NET 控制台项目 → `ClientWebSocket` 或 `TcpClient` → 多线程并发。
- 关键代码（C# 片段）：
  ```csharp
  for (int i = 0; i < conn; i++)
  {
      _ = Task.Run(async () =>
      {
          var ws = new ClientWebSocket();
          await ws.ConnectAsync(new Uri("ws://127.0.0.1:9000"), CancellationToken.None);
          var sw = Stopwatch.StartNew();
          await ws.SendAsync(ping, WebSocketMessageType.Binary, true, default);
          await ws.ReceiveAsync(pong, default);
          sw.Stop();
          histogram.Record(sw.ElapsedMilliseconds);
      });
  }
  ```
- 把“连接数、RTT 直方图”实时打印到控制台。  
  • 做完得到：可执行文件 `ImBench.exe -c 连接数 -t 秒数`。

---

4. 跑一次“阶梯式找极限”  
   • 为什么：先知道 Windows Loopback 能扛多少。  
   • 怎么做：PowerShell 循环：

```powershell
1000,3000,6000,10000,15000,20000 | %{
    .\ImBench.exe -c $_ -t 60 | Tee-Object "rtt_$_.log"
}
```

• 做完得到：一组 rtt\_\*.log → 找到 P99 首次 > 10 ms 的临界连接数（假设 12 k）。

---

5. 用 Windows Performance Recorder (WPR) 抓瓶颈  
   • 为什么：CPU、GC、线程调度、网络栈都要可视化。  
   • 怎么做：

1) 安装 Windows ADK → 打开“Windows Performance Recorder” → 选 CPU、Network → Start。
2) 跑 ImBench.exe -c 12000 -t 30。
3) Stop → 用 Windows Performance Analyzer（WPA）打开 `.etl`，看 `System\Context Switches`, `.NET CLR\GC Heap Size`, `TCP\Connections Established`。  
   • 做完得到：一张火焰图/时间线，告诉你“是 GC、线程切换还是网卡软中断”导致 10 ms 抖动。

---

6. 做一次 1 w 连接 soak（稳定性）  
   • 为什么：Windows Loopback 也可能出现句柄泄露或 TCP TIME_WAIT。  
   • 怎么做：

```powershell
.\ImBench.exe -c 10000 -t 7200   # 2 小时
```

期间用资源监视器（resmon）或任务管理器实时看句柄、内存、网络。  
• 做完得到：若 2 h 内 RTT 直方图不变、句柄数不涨，稳定性通过。

---

7. 用 ApacheBench(ab) 或 JMeter 做 HTTP 旁路验证（可选）  
   • 为什么：如果你的 IM 还有 HTTP 接口（登录、心跳），可以顺带压。  
   • 怎么做：

- ab：
  ```powershell
  ab -n 100000 -c 100 http://localhost:9000/api/login
  ```
- JMeter：GUI 里新建 Thread Group → 填 10000 线程 → 循环 100 次 → 运行。  
  • 做完得到：HTTP 接口的 QPS、P99，与 WebSocket/TCP 结果互相印证。

---

8. 把脚本搬进 CI（GitHub Actions on Windows Runner）  
   • 为什么：防止以后代码回退。  
   • 怎么做：`.github/workflows/bench.yml`

```yaml
- run: dotnet run --project Server --urls http://localhost:9000 &
- run: Start-Sleep 5
- run: dotnet run --project ImBench -- 10000 30
- run: cat rtt_10000.log | findstr P99
```

若 P99 > 10 ms，则 job fail。  
• 做完得到：每次 PR 自动跑 30 秒压测，性能回退立刻红叉。

---

小结  
| 阶段 | Win11 工具链 | 关键产出 |  
|---|---|---|  
| 调参 | reg / netsh | 5 w 句柄 + 6 w 端口 |  
| 靶子 | VS + Kestrel | 本机 IM 服务 |  
| 负载 | 自写 ImBench.exe | RTT 直方图 |  
| 瓶颈 | WPR + WPA | CPU/GC/网络火焰图 |  
| 稳定 | 2h soak | 句柄、内存零增长 |  
| 回归 | GitHub Actions | CI 红绿状态 |

按上面 8 步走，你就能在 Windows 11 单机 VS 环境下完成“2 w 连接内 10 ms RTT”的全部压测与回归。

## 设计模式

### Acto模式，逻辑解耦

“Acto 模式，逻辑解耦”这句话中的 **Acto 并不是 Actor/演员拼写错误**，而是指一种**面向组件、强调“接口 + 服务”的轻量级架构风格**，其核心目标就是**把复杂业务逻辑拆成可独立开发、独立测试、独立部署的小块（组件）**，从而降低系统耦合度。下面把它拆成两句话讲清楚：

------------------------------------------------
1. Acto 模式到底是什么  
------------------------------------------------
• 概念来源：国内工程团队把“**A**ssemble **C**omponents **T**hrough **O**rchestration”（通过编排去装配组件）的首字母缩写成了 **Acto**。  
• 关键特征：  

  1. 每个功能被封装成一个 **可插拔的 Service 组件**，对外只暴露接口；  
  2. 组件之间 **不直接调用**，而是走“事件/消息/接口”完成解耦；  
  3. 系统运行时通过 **编排器（Orchestrator）** 把这些组件按业务场景动态拼装起来。  
• 一句话总结：**“把系统拆成乐高积木，再用胶水（编排器）按场景粘成不同的形状”。**

------------------------------------------------
2. “逻辑解耦”在 Acto 模式里怎么落地  
------------------------------------------------
| 传统做法（紧耦合）                    | Acto 模式（逻辑解耦）                                  |
| ------------------------------------- | ------------------------------------------------------ |
| 订单模块直接 `new PayService().pay()` | 订单模块发一个“支付请求事件”，支付组件监听事件完成扣款 |
| 改支付逻辑需要重新编译订单代码        | 只需替换或升级支付组件，其他代码 0 改动                |
| 单元测试必须拉起整个应用              | 每个组件可独立单元测试，用 mock 消息即可               |

解耦手段归纳为三板斧：  
1. **接口解耦**：组件只依赖接口，不依赖实现；  
2. **时间解耦**：用消息队列把同步调用变异步；  
3. **部署解耦**：每个组件打成独立 DLL/Jar/容器，上线互不影响。

------------------------------------------------
3. 举个最小例子（伪代码）  
------------------------------------------------
```csharp
// 订单组件：只发事件，不 care 谁处理
bus.Publish(new OrderCreatedEvent(orderId:123, amount:99));

// 支付组件：监听事件，真正的扣款逻辑在这里
bus.Subscribe<OrderCreatedEvent>(ev => Pay(ev.orderId, ev.amount));
```
如果明天想换成“先红包抵扣再支付”，**新增一个红包组件即可**，订单代码一行不用改——这就是 Acto 模式通过逻辑解耦带来的扩展力。

------------------------------------------------
一句话背下来  
**Acto 模式 = “把系统切成小服务 + 用事件/接口拼装”**；**逻辑解耦 = “让任何一块积木坏了或被换掉时，其他积木毫无感知”**。

### 
