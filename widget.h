/**
 * @brief 客户端HTTP请求类
 * @author Bunny GitHub: bunny-chz
 * @date 2022/10/15
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMetaObject>
#include <QEventLoop>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    /** 上传文件路径 */
    QString filePath = "";
    /** 上传文件MimeType */
    QString mimeType = "text/plain";

    /** GET请求获取服务器发送的文本 */
    void getTextFromServer();
    /** GET文本请求的响应处理 */
    void getTextReply(QNetworkReply *reply);
    /** POST文本text键值到服务器 */
    void postTextToServer(QString str);
    /** POST文本text键值到服务器的响应处理 */
    void postTextReply(QNetworkReply *reply);

    /** GET请求获取服务器分享的文件 */
    void getFileFromServer();
    /** GET文件请求的响应处理 */
    void getFileReply(QNetworkReply *reply);
    /** POST文件到服务器 */
    void postFileToServer(QString filePath, QString mimeType);
    /** POST文件到服务器的响应处理 */
    void postFileReply(QNetworkReply *reply);
    /** 保存下载文件记录 */
    bool saveText(QString strContent,QString fileName);
private slots:

    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
