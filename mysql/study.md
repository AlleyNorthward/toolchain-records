&emsp;&emsp;@author 巷北  
&emsp;&emsp;@time 2026-01-14 15:51:58  

- [基本操作](#基本操作)
    - [可视化](#可视化)
    - [基本SELECT](#基本SELECT)
         - [比较查询](#比较查询)
         - [其它简单查询](#其它简单查询)
- [复杂查询](#复杂查询)
    - [别名](#别名)

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













