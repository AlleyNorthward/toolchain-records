下面的这个模版是`ai` 的, 感觉还是不错的. 仅作为参考吧.
## 工具名称：Vulkan SDK

### 版本：
- Vulkan SDK 版本：1.4.335.0
- 下载链接：[Vulkan SDK 下载页面](https://vulkan.lunarg.com/sdk/home)

### 安装步骤：
1. 下载 SDK
2. 解压到指定目录 `F:/Vulkan/`
3. 设置环境变量：
   - `VULKAN_SDK = F:/Vulkan/VulkanSDK/1.4.335.0`
4. 配置 CMake：
   - 在 `CMakeLists.txt` 中添加以下路径：
     ```cmake
     find_package(Vulkan REQUIRED)
     ```
### 遇到的问题：
- 问题：CMake 找不到 Vulkan 配置文件
  - 解决方案：确保 Vulkan SDK 安装路径正确，并设置 `CMAKE_PREFIX_PATH` 指向 Vulkan SDK 的 `cmake` 目录。

### 参考文档：
- [Vulkan 官方文档](https://www.khronos.org/vulkan/)












