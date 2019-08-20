/********************************************************************************
** Form generated from reading UI file 'time_dlg.ui'
**
** Created: Thu Sep 6 10:04:16 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIME_DLG_H
#define UI_TIME_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_time_Dlg
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpinBox *year_spinBox;
    QLabel *label;
    QSpinBox *month_spinBox;
    QLabel *label_2;
    QSpinBox *day_spinBox;
    QLabel *label_3;
    QPushButton *saveBtn;
    QPushButton *cancel_Btn;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *hour_spinBox;
    QLabel *label_dot;
    QSpinBox *min_spinBox;

    void setupUi(QDialog *time_Dlg)
    {
        if (time_Dlg->objectName().isEmpty())
            time_Dlg->setObjectName(QString::fromUtf8("设置"));
        time_Dlg->resize(320, 210);
        time_Dlg->setMinimumSize(QSize(320, 210));
        time_Dlg->setMaximumSize(QSize(320, 210));
        horizontalLayoutWidget = new QWidget(time_Dlg);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 70, 281, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        year_spinBox = new QSpinBox(horizontalLayoutWidget);
        year_spinBox->setObjectName(QString::fromUtf8("year_spinBox"));
        year_spinBox->setWrapping(true);
        year_spinBox->setAlignment(Qt::AlignCenter);
        year_spinBox->setMinimum(2000);
        year_spinBox->setMaximum(2050);

        horizontalLayout->addWidget(year_spinBox);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        month_spinBox = new QSpinBox(horizontalLayoutWidget);
        month_spinBox->setObjectName(QString::fromUtf8("month_spinBox"));
        month_spinBox->setBaseSize(QSize(0, 0));
        month_spinBox->setWrapping(true);
        month_spinBox->setAlignment(Qt::AlignCenter);
        month_spinBox->setMinimum(1);
        month_spinBox->setMaximum(12);

        horizontalLayout->addWidget(month_spinBox);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        day_spinBox = new QSpinBox(horizontalLayoutWidget);
        day_spinBox->setObjectName(QString::fromUtf8("day_spinBox"));
        day_spinBox->setWrapping(true);
        day_spinBox->setAlignment(Qt::AlignCenter);
        day_spinBox->setMinimum(1);
        day_spinBox->setMaximum(31);

        horizontalLayout->addWidget(day_spinBox);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        saveBtn = new QPushButton(time_Dlg);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setGeometry(QRect(180, 150, 61, 27));
        cancel_Btn = new QPushButton(time_Dlg);
        cancel_Btn->setObjectName(QString::fromUtf8("cancel_Btn"));
        cancel_Btn->setGeometry(QRect(70, 150, 61, 27));
        horizontalLayoutWidget_2 = new QWidget(time_Dlg);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(80, 20, 136, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        hour_spinBox = new QSpinBox(horizontalLayoutWidget_2);
        hour_spinBox->setObjectName(QString::fromUtf8("hour_spinBox"));
        hour_spinBox->setWrapping(true);
        hour_spinBox->setAlignment(Qt::AlignCenter);
        hour_spinBox->setMaximum(23);

        horizontalLayout_2->addWidget(hour_spinBox);

        label_dot = new QLabel(horizontalLayoutWidget_2);
        label_dot->setObjectName(QString::fromUtf8("label_dot"));
        label_dot->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_dot);

        min_spinBox = new QSpinBox(horizontalLayoutWidget_2);
        min_spinBox->setObjectName(QString::fromUtf8("min_spinBox"));
        min_spinBox->setWrapping(true);
        min_spinBox->setAlignment(Qt::AlignCenter);
        min_spinBox->setMaximum(59);

        horizontalLayout_2->addWidget(min_spinBox);


        retranslateUi(time_Dlg);

        QMetaObject::connectSlotsByName(time_Dlg);
    } // setupUi

    void retranslateUi(QDialog *time_Dlg)
    {
        time_Dlg->setWindowTitle(QApplication::translate("time_Dlg", "\346\227\266\351\227\264\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("time_Dlg", "\345\271\264", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("time_Dlg", "\346\234\210", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("time_Dlg", "\346\227\245", 0, QApplication::UnicodeUTF8));
        saveBtn->setText(QApplication::translate("time_Dlg", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        cancel_Btn->setText(QApplication::translate("time_Dlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_dot->setText(QApplication::translate("time_Dlg", ":", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class time_Dlg: public Ui_time_Dlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIME_DLG_H
