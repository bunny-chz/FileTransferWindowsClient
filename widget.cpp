/**
 * @brief 客户端HTTP请求类
 * @author Bunny GitHub: bunny-chz
 * @date 2022/10/15
 */  
#include "widget.h"
#include "ui_widget.h"
#include<QIcon>
#include<QFile>
#include<QSettings>
#include<QMessageBox>
#include <QFileDialog>
#include<QMimeType>
#include<QMimeDatabase>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置标题
    this->setWindowTitle("文件快传客户端");
    //设置图标
    this->setWindowIcon(QIcon(":/res/app_icon.png"));
    //读取配置文件，显示当前设置的服务器主机端口
    QSettings *hostPort = new QSettings("HostPortSetting.ini", QSettings::IniFormat);
    ui->lineEdit->setText(hostPort->value("hostPort").toString());
}

Widget::~Widget()
{
    delete ui;
}
void Widget::getTextFromServer()
{
    QSettings *hostPort = new QSettings("HostPortSetting.ini", QSettings::IniFormat);
    //先判断是否设置了主机端口
    if(!hostPort->value("hostPort").toString().isEmpty()){
        QNetworkRequest request1;
        QNetworkAccessManager nam;
        connect(&nam, &QNetworkAccessManager::finished, this, &Widget::getTextReply);
        //设置请求链接
        request1.setUrl(QUrl("http://" + hostPort->value("hostPort").toString() + "/textStoC"));
        QNetworkReply *reply = nam.get(request1);

        //开启事件循环，直到请求完成
        QEventLoop loop;
        connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
        loop.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("服务器地址为空!");
        msgBox.setInformativeText("请在设置服务器主机框内输入地址，并点击按钮保存设置");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
}
void Widget::getTextReply(QNetworkReply *reply)
{
    QString textStr = reply->readAll();
    qDebug() << "getTextReply ---> " + textStr;
    if(textStr.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("服务器没有发送问文本消息！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
    else{
        textStr.replace("#-#-#","\n\n");
        ui->textEdit_4->setText(textStr);
    }
}
void Widget::postTextToServer(QString str)
{
    QSettings *hostPort = new QSettings("HostPortSetting.ini", QSettings::IniFormat);
    //先判断是否设置了主机端口
    if(!hostPort->value("hostPort").toString().isEmpty()){
        QNetworkRequest request1;
        QNetworkAccessManager nam;
        connect(&nam, &QNetworkAccessManager::finished, this, &Widget::postTextReply);

        request1.setUrl(QUrl("http://" + hostPort->value("hostPort").toString() + "/textCtoS"));

        //请求头设置
        request1.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded;charset=utf-8"));
        QString data = QString("text=" + str);
        QNetworkReply* reply = nam.post(request1,data.toUtf8());        //post请求头+传输的数据

        //开启事件循环，直到请求完成
        QEventLoop loop;
        connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
        loop.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("服务器地址为空!");
        msgBox.setInformativeText("请在设置服务器主机框内输入地址，并点击按钮保存设置");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
}
void Widget::postTextReply(QNetworkReply *reply)
{
    QString strReply = reply->readAll();
    qDebug() << "postFileReply ---> " << strReply;
    if(strReply.contains("操作成功！")){
        QMessageBox msgBox;
        msgBox.setText("文本消息发送成功！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
}
void Widget::getFileFromServer()
{
    QSettings *hostPort = new QSettings("HostPortSetting.ini", QSettings::IniFormat);
    //先判断是否设置了主机端口
    if(!hostPort->value("hostPort").toString().isEmpty()){
        QNetworkRequest request1;
        QNetworkAccessManager nam;
        connect(&nam, &QNetworkAccessManager::finished, this, &Widget::getFileReply);
        request1.setUrl(QUrl("http://" + hostPort->value("hostPort").toString() + "/fileStoC"));
        QNetworkReply *reply = nam.get(request1);    //get请求头

        //开启事件循环，直到请求完成
        QEventLoop loop;
        connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
        loop.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("服务器地址为空!");
        msgBox.setInformativeText("请在设置服务器主机框内输入地址，并点击按钮保存设置");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
}
void Widget::getFileReply(QNetworkReply *reply)
{
    QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
    qDebug()<<"contentType" << contentType.toString();
    QString dirName = "C:/FileTransfer Files/Download/";
    QDir dir(dirName);
    if(!dir.exists())
    {
        dir.mkdir(dirName);
        qDebug() << "dir.mkdir ---> " <<"创建成功";
    }
    QFile* file=new QFile(dirName,reply);
    QDir::setCurrent(dirName);
    //设置打开的路径
    file->setFileName(contentType.toString());
    if(!file->open(QFile::WriteOnly)){
        qDebug()<<"文件打开失败";
    }
    file->write(reply->readAll());
    QString srtContent = "时间: " + QDate::currentDate().toString("yyyy/MM/dd") + " " + QTime::currentTime().toString("HH:mm:ss") + "\n" + contentType.toString() + "\n";
    saveText(srtContent,"FileStoCLog.txt");
    connect(reply,&QNetworkReply::finished,this,[file](){
        file->close();
        file->deleteLater();
    });

}
bool Widget::saveText(QString strContent,QString fileName)
{
    QString dirName = "C:/FileTransfer Files/AppConfig/";
    QDir dir(dirName);
    if(!dir.exists())
    {
        dir.mkdir(dirName);
        qDebug() << "dir.mkdir ---> " <<"创建成功";
    }
    QFile *file = new QFile;
    QDir::setCurrent(dirName);
    //设置打开的路径
    file->setFileName(fileName);
    //只写
    bool openOK = file->open(QIODevice::Append);
    if(openOK)
    {
        //问件指针关联文本流
        QTextStream stream(file);
        //UTF-8
        stream.setCodec("UTF-8");
        stream<<strContent;
        //关闭文件
        file->close();
        delete file;
        //返回是否保存成功
        return true;
    }
    return false;
}

void Widget::postFileToServer(QString filePath, QString mimeType)
{
    QSettings *hostPort = new QSettings("HostPortSetting.ini", QSettings::IniFormat);
    //先判断是否设置了主机端口
    if(!hostPort->value("hostPort").toString().isEmpty()){
        QFileInfo fileInfo(filePath);
        qDebug() << "fileInfo.fileName() ---> " << fileInfo.fileName();
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType,this);
        QFile *file = new QFile(filePath);
        QHttpPart filePart;
        QString requestFormat = QString::fromUtf8("form-data; name=\"file\"; filename=\"" + fileInfo.fileName().toUtf8()+ "\"");
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(requestFormat));
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mimeType));
        bool openOK = file->open(QIODevice::ReadOnly);
        if(openOK){
            filePart.setBodyDevice(file);
        }
        multiPart->append(filePart);
        //http请求
        QNetworkRequest request1;
        QNetworkAccessManager nam;
        connect(&nam, &QNetworkAccessManager::finished, this, &Widget::postFileReply);
        request1.setUrl(QUrl("http://" + hostPort->value("hostPort").toString() + "/fileCtoS"));    //要请求的网址

        QNetworkReply* reply = nam.post(request1, multiPart);        //post请求头+传输的数据

        //开启事件循环，直到请求完成
        QEventLoop loop;
        connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
        loop.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("服务器地址为空!");
        msgBox.setInformativeText("请在设置服务器主机框内输入地址，并点击按钮保存设置");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }

}
void Widget::postFileReply(QNetworkReply *reply)
{
    QString strReply = reply->readAll();
    qDebug() << "postFileReply ---> " << strReply;
    if(strReply.contains("上传文件 操作成功！")){
        QMessageBox msgBox;
        msgBox.setText("文件上传成功！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
}
//发送文字给服务器，
void Widget::on_toolButton_2_clicked()
{
    if(ui->textEdit_3->toPlainText().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText(" 输入内容为空!");
        msgBox.setInformativeText("请在输入框内输入文本内容");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }else{
        QString str = ui->textEdit_3->toPlainText();
        postTextToServer(str);
    }
}
//按钮被点击后，下载服务器设置分享的文件
void Widget::on_toolButton_clicked()
{
    getTextFromServer();
}
//保存主机和端口号
void Widget::on_toolButton_3_clicked()
{
    QSettings *hostPort = new QSettings("HostPortSetting.ini", QSettings::IniFormat);
    hostPort->setValue("hostPort",ui->lineEdit->text());
}
//选择文件，得到文件的路径，用于后面的上传操作
void Widget::on_toolButton_4_clicked()
{
    this->filePath = QFileDialog::getOpenFileName(this,tr("选择文件分享给客户端"),"",tr("*"));
    if (filePath.isEmpty())
    {
        return;
    }
    QMimeDatabase db;
    QMimeType subFileMimeType = db.mimeTypeForFile(filePath);  //根据前面定义的文件名（含后缀）
    this->mimeType = subFileMimeType.name();  //使用name()将MimeType类型转为字符串类型
    qDebug() << "fileMimeType ---> " << mimeType;
    ui->label_8->setText("已选择的文件: " + filePath);
}
//读取
void Widget::on_toolButton_6_clicked()
{
    QString dirName = "C:/FileTransfer Files/AppConfig/";
    QDir dir(dirName);
    if(!dir.exists())
    {
        dir.mkdir(dirName);
        qDebug() << "dir.mkdir ---> " <<"创建成功";
    }
    QFile *file = new QFile;
    QDir::setCurrent(dirName);
    //设置打开的路径
    file->setFileName("FileStoCLog.txt");
    //只读
    bool openOK = file->open(QIODevice::ReadOnly);

    if(openOK)
    {
        //问件指针关联文本流
        QTextStream stream(file);
        //UTF-8
        stream.setCodec("UTF-8");
        QString str = stream.readAll();
        if(str.isEmpty()){
            ui->textBrowser->setText("无下载文件记录");
        }else{
            ui->textBrowser->setText(str);
        }
        //关闭文件
        file->close();
        delete file;
    }else{
        ui->textBrowser->setText("无下载文件记录");
    }
}
//清空下载日志
void Widget::on_toolButton_5_clicked()
{
    ui->textBrowser->setText("");
    QString dirName = "C:/FileTransfer Files/AppConfig/";
    QDir dir(dirName);
    if(!dir.exists())
    {
        dir.mkdir(dirName);
        qDebug() << "dir.mkdir ---> " <<"创建成功";
    }
    QFile *file = new QFile;
    QDir::setCurrent(dirName);
    //设置打开的路径
    file->setFileName("FileStoCLog.txt");
    //只写
    bool openOK = file->open(QIODevice::WriteOnly);
    if(openOK)
    {
        //问件指针关联文本流
        QTextStream stream(file);
        //UTF-8
        stream.setCodec("UTF-8");
        stream<<"";
        //关闭文件
        file->close();
        delete file;
    }
}
void Widget::on_toolButton_7_clicked()
{
    getFileFromServer();
}
//判断是否选择文件上传
void Widget::on_toolButton_8_clicked()
{
    if(filePath.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("没有选择文件！");
        msgBox.setInformativeText("请点击选择文件按钮选择");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,"好的");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }else{
        postFileToServer(filePath,mimeType);
    }
}
