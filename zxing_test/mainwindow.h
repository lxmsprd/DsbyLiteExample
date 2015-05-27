#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zxing/multi/GenericMultipleBarcodeReader.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>
#include <zxing/common/GlobalHistogramBinarizer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void on_pushButton_clicked();

    void  qrImage(const QString &path);

    std::vector<zxing::Ref<zxing::Result> > decode(zxing::Ref<zxing::BinaryBitmap> image, zxing::DecodeHints hints){
        zxing::Ref<zxing::Reader> reader(new zxing::MultiFormatReader);
        return std::vector<zxing::Ref<zxing::Result> >(1, reader->decode(image, hints));
    }
    std::vector<zxing::Ref<zxing::Result> > decode_multi(zxing::Ref<zxing::BinaryBitmap> image, zxing::DecodeHints hints){
        zxing::MultiFormatReader delegate;
        zxing::multi::GenericMultipleBarcodeReader reader(delegate);
        return reader.decodeMultiple(image, hints);
    }

private:
    Ui::MainWindow *ui;
//    zxing::MultiFormatReader reader;
//    zxing::multi::MultipleBarcodeReader * decoder;
};

#endif // MAINWINDOW_H
