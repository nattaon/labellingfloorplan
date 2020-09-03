/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 25), // "Button_deleteline_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 25), // "Button_openfolder_clicked"
QT_MOC_LITERAL(4, 64, 27), // "Button_selectfolder_clicked"
QT_MOC_LITERAL(5, 92, 28), // "Button_generatelabel_clicked"
QT_MOC_LITERAL(6, 121, 21), // "Button_zoomin_clicked"
QT_MOC_LITERAL(7, 143, 22), // "Button_zoomout_clicked"
QT_MOC_LITERAL(8, 166, 22), // "Button_nextimg_clicked"
QT_MOC_LITERAL(9, 189, 22), // "Button_previmg_clicked"
QT_MOC_LITERAL(10, 212, 26), // "Button_ccwrotation_clicked"
QT_MOC_LITERAL(11, 239, 25), // "Button_cwrotation_clicked"
QT_MOC_LITERAL(12, 265, 22), // "Button_saveimg_clicked"
QT_MOC_LITERAL(13, 288, 13), // "SelectImgFile"
QT_MOC_LITERAL(14, 302, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(15, 319, 4), // "item"
QT_MOC_LITERAL(16, 324, 3), // "col"
QT_MOC_LITERAL(17, 328, 10), // "SelectLine"
QT_MOC_LITERAL(18, 339, 9), // "ZoomImage"
QT_MOC_LITERAL(19, 349, 1), // "f"
QT_MOC_LITERAL(20, 351, 11), // "on_scroll_h"
QT_MOC_LITERAL(21, 363, 5), // "value"
QT_MOC_LITERAL(22, 369, 11) // "on_scroll_v"

    },
    "MainWindow\0Button_deleteline_clicked\0"
    "\0Button_openfolder_clicked\0"
    "Button_selectfolder_clicked\0"
    "Button_generatelabel_clicked\0"
    "Button_zoomin_clicked\0Button_zoomout_clicked\0"
    "Button_nextimg_clicked\0Button_previmg_clicked\0"
    "Button_ccwrotation_clicked\0"
    "Button_cwrotation_clicked\0"
    "Button_saveimg_clicked\0SelectImgFile\0"
    "QTreeWidgetItem*\0item\0col\0SelectLine\0"
    "ZoomImage\0f\0on_scroll_h\0value\0on_scroll_v"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    2,  105,    2, 0x08 /* Private */,
      17,    2,  110,    2, 0x08 /* Private */,
      18,    1,  115,    2, 0x08 /* Private */,
      20,    1,  118,    2, 0x08 /* Private */,
      22,    1,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   15,   16,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Button_deleteline_clicked(); break;
        case 1: _t->Button_openfolder_clicked(); break;
        case 2: _t->Button_selectfolder_clicked(); break;
        case 3: _t->Button_generatelabel_clicked(); break;
        case 4: _t->Button_zoomin_clicked(); break;
        case 5: _t->Button_zoomout_clicked(); break;
        case 6: _t->Button_nextimg_clicked(); break;
        case 7: _t->Button_previmg_clicked(); break;
        case 8: _t->Button_ccwrotation_clicked(); break;
        case 9: _t->Button_cwrotation_clicked(); break;
        case 10: _t->Button_saveimg_clicked(); break;
        case 11: _t->SelectImgFile((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->SelectLine((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->ZoomImage((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->on_scroll_h((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_scroll_v((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
