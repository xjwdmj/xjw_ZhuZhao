# xjw_ZhuZhao

基于 Qt 6 + MSVC2022 的光度立体(Photometric Stereo)三维重建工具。

## 结构
- `src/PhotometricStereo` — 核心算法库(CMake)
- `src/zzGUI` — Qt 界面(.pro)
- `src/images` — 测试图像
- `src/bin` — 构建输出(不纳入版本控制)

## 构建
PhotometricStereo: 用 CMake 生成工程后编译
zzGUI: 用 Qt Creator 打开 `test_zzGUI.pro`
