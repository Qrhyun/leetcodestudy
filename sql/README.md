## 1.LEFT JOIN
> 要谁，谁在的那个表就是主表

这条 SQL 查询语句使用了 `LEFT JOIN` 来连接两个表：`Employees` 和 `EmployeeUNI`。`LEFT JOIN` 的作用是返回左表（`Employees` 表）的所有记录，即使右表（`EmployeeUNI` 表）中没有匹配的记录。下面是这条语句的详细解释：

### 表和字段

- **`Employees` 表**：这个表包含员工的信息，其中 `id` 字段是员工的唯一标识符，`name` 字段是员工的名字。
- **`EmployeeUNI` 表**：这个表可能包含与员工相关的唯一标识符信息，其中 `id` 字段与 `Employees` 表中的 `id` 字段相关联，`unique_id` 字段是员工的唯一标识符。

### 查询语句解析

```sql
SELECT EmployeeUNI.unique_id, Employees.name 
FROM Employees 
LEFT JOIN EmployeeUNI ON Employees.id = EmployeeUNI.id;
```

1. **选择字段**：
    - `EmployeeUNI.unique_id`：选择 `EmployeeUNI` 表中的 `unique_id` 字段。这意味着查询结果将包含每个员工的唯一标识符。
    - `Employees.name`：选择 `Employees` 表中的 `name` 字段。这意味着查询结果将包含每个员工的名字。

2. **数据来源**：
    - `FROM Employees`：指定查询的主表是 `Employees` 表。这意味着即使 `EmployeeUNI` 表中没有对应的记录，`Employees` 表中的所有记录也会被返回。

3. **连接类型**：
    - `LEFT JOIN EmployeeUNI`：指定使用左外连接来连接 `EmployeeUNI` 表。这意味着即使 `EmployeeUNI` 表中没有与 `Employees` 表匹配的记录，`Employees` 表中的所有记录仍然会被返回。

4. **连接条件**：
    - `ON Employees.id = EmployeeUNI.id`：指定连接条件是 `Employees` 表中的 `id` 字段与 `EmployeeUNI` 表中的 `id` 字段相等。这意味着只有当两个表中的 `id` 字段匹配时，才会从 `EmployeeUNI` 表中选择记录。

### 查询结果

- 如果 `EmployeeUNI` 表中有与 `Employees` 表匹配的记录，那么查询结果将包含 `EmployeeUNI` 表中的 `unique_id` 和 `Employees` 表中的 `name`。
- 如果 `EmployeeUNI` 表中没有与 `Employees` 表匹配的记录，那么查询结果将只包含 `Employees` 表中的 `name`，而 `unique_id` 列将显示为 `NULL`。

## 2.统计浏览次数
- [题目](https://leetcode.cn/problems/customer-who-visited-but-did-not-make-any-transactions/?envType=study-plan-v2&envId=sql-free-50)
```sql
SELECT customer_id, count(customer_id) count_no_trans
FROM Visits v 
LEFT JOIN transactions t 
ON v.visit_id = t.visit_id
WHERE transaction_id IS NULL
GROUP BY customer_id;
```
```sql
SELECT customer_id, COUNT(visit_id) AS count_no_trans
FROM Visits 
WHERE visit_id NOT IN (
    SELECT DISTINCT visit_id FROM transactions
    )
GROUP BY customer_id;
```