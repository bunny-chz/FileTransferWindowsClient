# FileTransferWindowsClient
基于C++ QT的文件快传Windows HTTP 客户端，

用于与搭建的QtWebApp HTTP服务器数据交换，

使用QT的QNetworkAccessManager类进行GET,POST请求，

服务器端用的是 QtWebApp


**开发环境**：

Windows QT 5.14.2


本应用可以实现向自建服务器发送文本信息和上传文件，从自建服务器接收文本信息和下载文件。

用到了QT的QNetworkAccessManager类，用HTTP的GET,POST请求，执行和服务器HTTP通信

其中QT电脑端上传下载文件有大小限制，过大会导致崩溃，或者文件数据错乱。

自定义的服务器接口:

http://IP:Port/ 网页端主页，客户端GET获取到一个网页

http://IP:Port/testLink 客户端GET请求，连接测试

http://IP:Port/textCtoSPage 客户端GET，获取到一个发送文本给服务器的操作网页

http://IP:Port/textCtoS 链接中带参数，客户端POST请求后，会给服务器发送文本信息，键值值为"text=???"

http://IP:Port/textStoC 客户端GET获取到服务器发送的信息

http://IP:Port/textStoCWeb 网页端GET获取到服务器发送的信息

http://IP:Port/fileCtoS 客户端POST请求后，会给服务器发送文件，POST请求内容标记为"file"

http://IP:Port/fileCtoSPage 网页端GET获取到一个发送文件给服务器的操作网页

http://IP:Port/fileStoCWeb 网页端GET服务器发送的文件

http://IP:Port/fileStoC 客户端GET服务器发送的文件



