#include "ImageWrapper.h"
#include <QColor>

using namespace zxing;

ImageWrapper::ImageWrapper(const QImage &image):LuminanceSource(image.width(),image.height()),image(image)
{
}

ImageWrapper::~ImageWrapper()
{
}


int ImageWrapper::getPixel(int x, int y) const
{
    QRgb pixel = image.pixel(x,y);
    return qGray(pixel);//((qRed(pixel) + qGreen(pixel) + qBlue(pixel)) / 3);
}

//QImage ImageWrapper::grayScaleImage(QImage::Format f)
//{
//    int width = getWidth();
//    int height =  getHeight();
//    int pix = 0;
//    QImage tmpImg(width, height, f);
//    for(int x =0; x < width; x++) {
//        for(int y = 0; y < height ; y++) {
//            pix = getPixel(x , y);
//            tmpImg.setPixel(x , y , qRgb(pix ,pix,pix));
//        }
//    }
//    return tmpImg;
//}

//QImage ImageWrapper::getOriginalImage()
//{
//    return image;
//}


ArrayRef<char> ImageWrapper::getRow(int y, zxing::ArrayRef<char> row) const
{
    int width = getWidth();
    if (!row){
        row = ArrayRef<char>(width);
    }
    for (int x = 0; x < width; x++)
        row[x] = getPixel(x,y);

    return row;
}

ArrayRef<char> ImageWrapper::getMatrix() const
{
    int width = getWidth();
    int height =  getHeight();
    ArrayRef<char> matrix(width*height);
    char* m = &matrix[0];
    ArrayRef<char> row(width);
    for(int y=0; y< height; y++){
        getRow(y,row);
        memcpy(m,&row[0],width);
        m += width * sizeof(char);
    }
    return matrix;
}

bool ImageWrapper::isCropSupported() const
{
    return true;
}

zxing::Ref<zxing::LuminanceSource> ImageWrapper::crop(int left, int top, int width, int height) const
{
    return Ref<LuminanceSource>(new ImageWrapper(image.copy(left,top,width,height)));
}
