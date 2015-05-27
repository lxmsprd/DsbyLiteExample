#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "ImageWrapper.h"
#include <QTime>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <zxing/ReaderException.h>

using namespace zxing;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    reader = new MultiFormatReader;
    //    decoder = new multi::GenericMultipleBarcodeReader(reader);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,tr("打开图片"),QString(),tr("Images (*.png *.jpg);"));
    this->ui->textEdit->clear();
    if (path.isEmpty()) return;
    this->ui->lineEdit->setText(path);
    qrImage(path);
}

void MainWindow::qrImage(const QString & path)
{
    QImage img;
    if (!img.load(path)) return;
    QTime tm;
    try {
        tm.start();
        std::vector<Ref<Result> > data;
        Ref<LuminanceSource> source(new ImageWrapper(img));
        Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(source));
        Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
        MultiFormatReader delegate;
        multi::GenericMultipleBarcodeReader reader(delegate);
        DecodeHints hints(DecodeHints::DEFAULT_HINT);
        hints.setTryHarder(false);
        data = reader.decodeMultiple(binary, hints);
        //         decoder->decodeMultiple(binary);
        int s = tm.elapsed();
        for (size_t i = 0;  i < data.size(); ++i) {
            Ref<Result> result = data.at(i);
            this->ui->textEdit->append(result->getText()->getText().c_str());
        }
        this->ui->textEdit->append(tr("一共用时：%1 ms").arg(s));
    }
    catch(zxing::Exception& e)
    {
        tm.elapsed();
        this->ui->textEdit->setPlainText(tr("解码失败：%1").arg(e.what()));
        return;
    }
}

