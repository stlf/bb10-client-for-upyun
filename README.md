**BB10 client for UPYUN**
=========

**简介：**
-
Blackberry 10 平台原生UPYUN客户端工具

  - 基于Qt实现了[UPYUN REST API(使用UPYUN签名认证)], 本客户端内的UpyunClient可作为跨平台的Qt UPYUN SDK来使用
  - 使用原生Cascades框架完成客户端的用户界面

基于BlackBerry 10 Native SDK 10.2编写, 支持运行Blackberry 10.2以上版本系统的设备, 本客户端已在[Z10]和[Q10]设备上进行了测试。

如果你发现bug，或有好的建议，请及时联系我([stlf@live.cn]). 很希望能与志同道合的你交流！

**下载和安装:**
-
应用安装包可以在**[这里下载]**   
目前安装应用最简单的方法：[方法一参见这里],  [方法二参见这里]  

**使用截图:**
-


-------------

**当前版本:**
-
    1.0.6

----
**功能：**
-
- 删除目录
- 上传文件
- 删除文件
- 获取目录文件列表
- 获取空间使用情况
- 文件外链打开浏览

--------

**History:**
-
> 2014-5-26 1.0.0：经过测试
> 2014-5-28 1.0.1：增加登录信息记忆功能
> 2014-5-29 1.0.2：增加文件上传、下载进度提示 
> 2014-5-31 1.0.5：修正下载中途被取消时，仍提示保存成功问题；修正多次点目录时可能引起的当前目录不正确问题。经过测试，增强了应用的稳定性。
> 2014-6-7 1.0.6：修正进度条有时显示不准确的问题，经过测试。

----
**TODO:**
-
> 增加登录信息记忆功能(已完成)
> 增加文件上传、下载进度提示 (已完成)
> 默认使用https, 增加安全性
> 增加图片处理功能
> ... ...

----
**License:**
-
[Apache License]


[UPYUN REST API(使用UPYUN签名认证)]:http://docs.upyun.com/api/#
[Z10]:http://uk.blackberry.com/smartphones/blackberry-z10.html
[Q10]:http://uk.blackberry.com/smartphones/blackberry-q10.html
[stlf@live.cn]:mailto:stlf@live.cn

[方法一参见这里]:http://iiberry.com/thread-26926-1-1.html
[方法二参见这里]:http://iiberry.com/thread-6872-1-1.html
[Apache License]: http://www.apache.org/licenses/

