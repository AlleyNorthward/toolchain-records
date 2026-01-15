&emsp;&emsp;@author 巷北  
&emsp;&emsp;@time 2026-01-14 15:51:58  

- [基本操作](#基本操作)
    - [可视化](#可视化)
    - [基本SELECT](#基本SELECT)
         - [比较查询](#比较查询)
         - [其它简单查询](#其它简单查询)
- [复杂查询](#复杂查询)
    - [别名](#别名)
    - [JOIN](#JOIN)

---

# 基本操作
## 可视化
&emsp;&emsp;我们摆弄数据库, 增删改查, 什么最重要呢? 我觉得还是查最重要. 不论怎么, 我们都需要将数据给可视化出来, 而这个查, 就是可视化的一部分.<br>
&emsp;&emsp;这里我们先说说基本的可视化操作, 然后在此基础上, 再进行其它的复杂操作.<br>

<div align="center">

|命令|含义|
|:---:|:---:|
|SHOW Databases|查看所有模式|
|SHOW Tables|查看该模式下所有表|
|DESCRIBE bill|查看该模式下bill表中的字段A|

</div>

&emsp;&emsp;当然, 还有很多东西, 肯定都能查看的, 比如触发器, 主键, 等等等等. 目前, 我们这些东西还用不到, 所以呢, 也就不先考虑这些东西. 我们主要关注的还是跟表相关的东西.<br>

## 基本SELECT
- 怎么理解这个东西呢? 看看下面这个基础公式.
    - `SELECT 列 FROM Tables WHERE 行?` 这是什么意思? `SELECT`, 选中的是`Tables` 的列. 如果是`SELECT*` 的话, 就是选中`Tables` 的所有列. `WHERE` 则是对行的限制, 这样我们就可以精确地获取这张二维表的某些数据.
    - `SELECT` 永远选择的是表的`列`. `WHERE` 永远限制的是表的行. (目前来看, 似乎一定是这样的.)
- 理解了这些, 基本查询的东西, 其实我们就都可以明确了. 对于这一张表, 我们可以轻松地获取某些数据.
- 下面呢, 我们就根据数据库大实验中的相关查询要求, 来总结理解一下其对应的操作吧.

### 比较查询
~~~mysql
-- 选择基础房价超过1000的房型
SELECT* FROM RoomType 
WHERE basePrice > 1000.00
~~~
~~~mysql
-- 查找2020年之前入职的员工
SELECT* FROM Employee
WHERE hireDate < '2020-01-01'
~~~
~~~mysql
-- 查找预定房数大于1的预定记录
SELECT* FROM Reservation
WHERE reservedRoomCount > 1;
~~~
- 我觉得, 这似乎是最基础的了. 但是呢, 为了将彼此联系起来, 我们需要知道看到问题, 如何快速获取其名称.
- 比如"选择基础房价超过`1000`的房型", 我们只知道房型表是`RoomType`, 但是不知道其价格字段是多少. 这样, 我们必须查看这张表的所有字段, 确定其名称后, 再填写. 所以, 需要先`DESCRIBE RoomType`, 再根据价格字段名, 编写上述代码. 
- 其余的也都是一个道理.

### 其它简单查询
~~~mysql
SELECT * FROM RoomType
WHERE area BETWEEN 20.00 AND 50.00;
~~~
~~~mysql
SELECT * FROM Reservation
WHERE roomTypeId IN (3,4,6);
~~~
- 这两个看起来相似, 但实际上还是很不同的. 第一个是范围比较查询, 第二个则是集合比较查询. 关键点, 我觉得应该是有没有`IN`, `NOT IN` 这俩关键字. 再比如如下的两个.
~~~mysql
SELECT * FROM Reservation
WHERE NOT (checkOutDate <= '2025-07-01' OR checkInDate >= '2025-07-10');
~~~
~~~mysql
SELECT * FROM Customer
WHERE membershipLevelId NOT IN (1,2);
~~~
- 也是同样的道理.
~~~mysql
SELECT * FROM Customer
WHERE name LIKE '测试%';
~~~
~~~mysql
SELECT * FROM Reservation
WHERE remark LIKE '%家庭%' OR remark LIKE '%儿童%';
~~~
- 这俩是字符串比较查询, 一种手段吧.

# 复杂查询
- 想要说复杂查询, 肯定不可能直接说, 还是要从简单的说起来, 这样才能够便于理解, :smile:. 
## 别名
- 别名这个东西其实很有意思, 复杂查询, 比如嵌套, `join` 查询等, 可以减少很多不必要的麻烦.
- 本质上, 对于选择的(比如`FROM`, `JOIN`)表, 我们可以后面直接`AS` + 别名的操作, 进行简化. 在`mysql` 中, `AS` 可以省略. 比如下面这个语句.
~~~mysql
SELECT r.* FROM Room r
WHERE r.roomTypeId IN (
  SELECT roomTypeId FROM RoomType WHERE basePrice > 1000.00
);
~~~
- 这里的`AS` 省略掉了. 但是呢, 我觉得还是需要添加上的, 这样便于我们理解. 另外, 这里用到了嵌套查询, 我们先不分析, 只关心别名的这部分.
~~~mysql
SELECT r.* FROM Room r
WHERE r.roomTypeId IN(
SELECT rt.roomTypeId FROM RoomType AS rt 
WHERE basePrice > 1000.00
);
~~~
- 上面的写法也是可以的, 本质上是一样的.
~~~mysql
SELECT s.checkInId, c.name AS customerName, r.roomId AS roomNumber, e.name AS handledBy
FROM Stay s
JOIN Customer c ON s.customerId = c.customerId
JOIN Room r ON s.roomId = r.roomId
LEFT JOIN Employee e ON s.staffId = e.employeeId
WHERE s.status = '在住';
~~~
- 这里, 我们可以看到, 不仅可以给整张表赋予别名(比如`Stay` 赋予了`s` 别名), 也可以给表的某一列赋予别名(比如`c.name`, 别名是customerName). 甚至可以有如下操作.
~~~mysql
SELECT sub.customerName
FROM (SELECT name AS customerName FROM Customer) AS sub
~~~
- 所以, `AS` 的操作对象可以是表, 可以是表的某列, 可以是函数, 可以是某个集合, 等等等等.

## JOIN
- 这个`JOIN`, 确实也是十分好玩的, :wink:. 这里还是以上面的那个为例, 说明一下. 
~~~mysql
SELECT s.checkInId, c.name AS customerName, r.roomId AS roomNumber, e.name AS handledBy
FROM Stay s
JOIN Customer c ON s.customerId = c.customerId
JOIN Room r ON s.roomId = r.roomId
LEFT JOIN Employee e ON s.staffId = e.employeeId
WHERE s.status = '在住';
~~~
- 如果, 没有`WHERE` 的存在, 所谓的`JOIN`, 确实是跨表链接了起来, 并且是完整地链接. 所以, `JOIN` 的存在, 可以让我们根据某些键, 准确地访问到除了这张表以外的东西.
- 对于`WHERE`, 仍然是限制行.
- 对于实现细节, 刚才从面向对象设计角度, 询问了`AI`, 又有了一定的理解. 表的每一行, 都是一个独立的对象. 所以, `SELECT` 筛选的是我们选择对象的特征, 而`WHERE` 则是筛选对象. 这样是不是更明确了呢?
- 那么对于`Stay` 和 `Customer`, 是什么关系呢? 这里我觉得还是关联关系, 甚至可以是聚合关系. 这样来看, 如果每一行, 都是类属性的话, 那么`Stay` 类, 包含了`Customer` 的关键`Id`, 那么就可以连接其所有数据. 
- 如果我们几乎排除组合关系(包含关系)的话, 那么大概率就是关联关系(如果有对方`ID`的话). 组合关系很好判断, 就是看生命周期是否同步. 在数据库中, 比如订单和订单项的关系, 就是组合关系.
- 扯的有点多了. 我们来看具体逻辑. 使用`JOIN`, 后面需要跟着`ON` 关键字. 这里的`ON`, 就是建立联系的意思. 比如`JOIN Customer c ON s.customerId = c.customerId`, 联系的建立就是`s.customerId` 与 `c.customerId`. 这里有个逻辑关系, 就是, 我们查询的表(`Stay`), 需要根据它所含有的某些属性(`customerId roomId staffIf`), 来找相关表(`Customer Room Employee`)进行链接(`JOIN`).
- 所以, 如果我们想使用链接的话, 先查看`FROM` 跟随的对象, 找到这张关键表. 然后根据这张表含有的属性, 再去找其它表链接, 从而起到跨表访问的效果.
- `FROM` 后, 能否跟随多个表对象?
    - 这也是我刚才的疑惑. 比如下面操作:`FROM a, b ...`. 在早期的`sql` 中, 确实是这样的. 但是后来被代替了. 被谁代替了呢? 就是`JOIN`, :joy:. 也就是说, 我们现在所做的`JOIN`, 其实本质上就是`FROM` 了多个对象.
- 感觉`JOIN` 基础似乎也都说完了, 那就先到这里吧.











