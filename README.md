# Bottom Wallpaper

让 [bottom](https://github.com/ClementTsang/bottom) 变成你的壁纸

## 安装

安装 Windows terminal 和 bottom，并为 Windows terminal 配置一个名为 Bottom 的 Profile。你可以为这个 Profile 配置背景图片来作为你的壁纸。

配置示例：

```json
            {
                "guid": "{84bd1aa7-8718-49b6-ae34-2be510209310}",
                "hidden": false,
                "commandline": "btm",
                "name": "Bottom",
                "backgroundImage": "path/to/pic",
                "backgroundImageOpacity": 0.3
            }
```

然后编译本项目：

```
g++ bottom-wallpaper.cxx utils.cxx -o bottom-wallpaper
```

运行 `bottom-wallpaper` 即可

## 截图

![demo](./demo.png)
