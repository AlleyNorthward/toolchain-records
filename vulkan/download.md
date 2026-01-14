&emsp;&emsp;@author 巷北  
&emsp;&emsp;@time 2026-01-14 13:44:45  

- [版本](#版本)
- [下载地址](#下载地址)
- [下载选项](#下载选项)
- [操作](#操作)
- [构建](#构建)

## 版本
`1.4.335.0`
## 下载地址
<!-- [下载地址](https://vulkan.lunarg.com/sdk/home "下载地址") -->
<a href="https://vulkan.lunarg.com/sdk/home" title="下载地址">下载地址</a>
## 下载选项
- 有挺多选项的. 我选择了`5` 个, 但名字忘了, 记得有`glm`, 数学相关的库, `sdl`, 用于显示的, 还有一个`pdb`, 用于调试的. 还有俩, 我也忘了.
## 操作
- 下载后, 似乎会自动添加到环境路径中去.
- 关键是如何使用. 可以先进入下载的`bin` 目录中去, 有个`vulkanCapsViewer.exe` 和 `vulkaninfoSDK.exe`(可以直接`vulkaninfo`, 也可以`vulkaninfo --html`), 有啥用我也不知道.
- 整体上来看, 似乎就这么多操作吧. 但是光有这些肯定是远远不够的, 最终要的是如何构建, 这才是最重要的.
## 构建
- 在`bin`同目录下, 有个`cmake` 跟`templates` 文件夹. 其中, `cmake`是`sdl`系列的`cmake`, 并不是`vulkan`的. 而`vulkan`的相关`cmake`, `cmake` 官方都集成了.
- 在`templates` 中, 有`vulkan`官方提供的参考代码. 但是, 怎么运行呢? 
- 官方期望我们直接在`visual stdio` 中运行, 但是我期望自己构建好`cmake`, 通过终端运行.
- 但是想运行还是非常困难的, 我也是历经了千辛万苦才找到的出路.
~~~cmake
cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(VulkanTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Vulkan::Vulkan)

get_target_property(MAIN_INCLUDE_DIRS main INCLUDE_DIRECTORIES)
message(STATUS "Main target include directories: ${MAIN_INCLUDE_DIRS}")
~~~
-这是第一个`cmake` 运行代码. 后面的两句是`debug` 用的, 无关紧要. 前面的感觉也没有什么好说的, 主要是`find_package`弄好即可.
~~~cmake
cmake_minimum_required(VERSION 3.25)
project(VulkanTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLM_INCLUDE_DIR "F:/Vulkan/VulkanSDK/1.4.335.0/Include")
set(SDL2_DIR "F:/Vulkan/VulkanSDK/1.4.335.0/cmake")

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)
add_executable(main main.cpp)

target_include_directories(main PRIVATE ${GLM_INCLUDE_DIR})
target_link_libraries(main PRIVATE Vulkan::Vulkan SDL2::SDL2)
~~~
- 接下来的, 用到了`glm`库以及`sdl2`. 上面的是完整的可执行代码. 但是, 其实之前还有一个. 当时的情况是, 我将`sdl`的`cmake`搜索路径添加到了环境变量中了, 但是我不确定是否有效. 不过在当时的代码下, 是可以正常运行的. 后来我将环境中对应的路径都删除掉了, 代码也就无法运行. 之后就改成了如今的这样. 对于`SDL2_DIR`, 是`cmake` 的用法, 用于帮助寻找`SDL2`的存在路径. 也就是对于`xxx_DIR`, 帮助寻找`find_package(xxx)`的相关路径的.
- 另外, 在`glm`中, 也有`CMakeLists` 相关的东西, 但是我不确定如何导包, 所以只能采用这种方式, 也就是指定头文件的方式运行代码.
- 看起来确实很简单, 但是也必须要有自己的理解. 所以需要学的东西还有很多.
