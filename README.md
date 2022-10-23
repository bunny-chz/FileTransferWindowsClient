# FileTransferWindowsClient
基于C++ QT的文件快传Windows HTTP 客户端，

用于与搭建的QtWebApp HTTP服务器进行数据交换，

使用QT的QNetworkAccessManager类进行GET,POST请求


-----------------------------------------------------------

这个是自定义文件传输软件系统的一部分---电脑的客户端

可以在局域网内基于HTTP协议，实现电脑，安卓，网页浏览器三端数据互通

电脑服务器端请看这里（用到了QtWebApp）

https://github.com/bunny-chz/FileTransferWindowsServer

手机端服务器端和客户端（用到了NanoHTTPD,Retrofit）

https://github.com/bunny-chz/FileTransferAndroid

----------------------------------------------------------

**开发环境**

Windows QT 5.14.2

------------------------

本应用可以实现向自建服务器发送文本信息和上传文件，从自建服务器接收文本信息和下载文件。

用到了QT的QNetworkAccessManager类，用HTTP的GET,POST请求，执行和服务器HTTP通信

其中QT电脑端上传下载文件有大小限制，测试得知200MB以内吧，过大会导致崩溃，或者文件数据错乱。

具体实现请看代码。


**自定义的服务器接口**

说明：下面的IP和Port为设备所属网络环境的IP和端口，只支持HTTP

textCtoS 即是 text from Client to Server的缩写，其他以此类推


http://IP:Port/ 网页端主页，客户端GET获取到一个网页

http://IP:Port/testLink 客户端GET请求，连接测试

http://IP:Port/textCtoSPage 客户端GET，获取到一个发送文本给服务器的操作网页

http://IP:Port/textCtoS 链接中带参数，客户端POST请求后，会给服务器发送文本信息，键值为"text=???"

http://IP:Port/textStoC 客户端GET获取到服务器发送的信息

http://IP:Port/textStoCWeb 网页端GET获取到服务器发送的信息

http://IP:Port/fileCtoS 客户端POST请求后，会给服务器发送文件，POST请求内容标记为"file"

http://IP:Port/fileCtoSPage 网页端GET获取到一个发送文件给服务器的操作网页

http://IP:Port/fileStoCWeb 网页端GET服务器发送的文件

http://IP:Port/fileStoC 客户端GET服务器发送的文件

---------------------------------------------------

界面预览

![image](https://user-images.githubusercontent.com/57706599/197377959-746083e8-d3a3-485d-955c-b5482c601f2d.png)

