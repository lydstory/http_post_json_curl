#include "widget.h"
#include "ui_widget.h"
#include "json/json.h"
#include "httpclient.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_exit_clicked()
{
    Json::Value value;
    value["cmd"] = Json::Value("generateOutFile");
    value["filename"] = Json::Value("50001");
    value["watermark"] = Json::Value("11101010011110110000111101010011");
    value["wmoperater"] = Json::Value("embedWM");
    value["backup1"] = Json::Value("");
    value["backup2"] = Json::Value("");
    value["format"] = Json::Value("pdf");
    Json::Reader reader;
    std::string strPostData = value.toStyledString();
    string strUrl = "http://192.168.5.162:8100/postwatermark";
    CHttpClient httpclient;
    std::string  strResponse;
   int nErrCode = httpclient.Put(strUrl, strPostData, strResponse, 10);

      qDebug() <<"sfsdfsfsd"<<endl;
}
