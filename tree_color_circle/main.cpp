#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

class ImageCircle : public QWidget
{
    Q_OBJECT
public:
    ImageCircle()=default;
    ImageCircle(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void oneColor();
    void twoColor();
    void threeColor();
private:
    QPixmap mCurrentColorPixmap;
    QPixmap mOneColorPixmap;
    QPixmap mTwoColorPixmap;
    QPixmap mThreeColorPixmap;
};
ImageCircle::ImageCircle(QWidget *parent)
{
    setParent(parent);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mOneColorPixmap = QPixmap("C:/files/red_circle.png");
    mTwoColorPixmap = QPixmap("C:/files/yellow_circle.png");
    mThreeColorPixmap = QPixmap("C:/files/green_circle.png");
    mCurrentColorPixmap = mOneColorPixmap;
    setGeometry(mCurrentColorPixmap.rect());
}

void ImageCircle::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(),mCurrentColorPixmap);
}

QSize ImageCircle::sizeHint() const
{
    return QSize(200, 200);
}

QSize ImageCircle::minimumSizeHint() const
{
    return QSize(100,100);
}

void ImageCircle::oneColor()
{
    mCurrentColorPixmap = mOneColorPixmap;
    update();
}

void ImageCircle::twoColor()
{
    mCurrentColorPixmap =  mTwoColorPixmap;
    update();
}

void ImageCircle::threeColor()
{
    mCurrentColorPixmap = mThreeColorPixmap;
    update();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto *myWidget = new QWidget;
    ImageCircle circle (nullptr);
    auto *slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);
    auto *layout = new QVBoxLayout(myWidget);
    layout->addWidget(&circle);
    layout->addWidget(slider);
    QObject::connect(slider, &QSlider::valueChanged, [&circle](int newValue)
    {
        if(newValue<=33){
            circle.oneColor();
        }
        else if(newValue>66){
            circle.threeColor();
        }
        else{
            circle.twoColor();
        }
    });
    myWidget->setFixedSize(200, 220);
    myWidget->show();
    return app.exec();
}

#include <main.moc>
