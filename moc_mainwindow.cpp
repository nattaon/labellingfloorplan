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
    QByteArrayData data[20];
    char stringdata0[305];
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
QT_MOC_LITERAL(10, 212, 13), // "SelectImgFile"
QT_MOC_LITERAL(11, 226, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(12, 243, 4), // "item"
QT_MOC_LITERAL(13, 248, 3), // "col"
QT_MOC_LITERAL(14, 252, 10), // "SelectLine"
QT_MOC_LITERAL(15, 263, 9), // "ZoomImage"
QT_MOC_LITERAL(16, 273, 1), // "f"
QT_MOC_LITERAL(17, 275, 11), // "on_scroll_h"
QT_MOC_LITERAL(18, 287, 5), // "value"
QT_MOC_LITERAL(19, 293, 11) // "on_scroll_v"

    },
    "MainWindow\0Button_deleteline_clicked\0"
    "\0Button_openfolder_clicked\0"
    "Button_selectfolder_clicked\0"
    "Button_generatelabel_clicked\0"
    "Button_zoomin_clicked\0Button_zoomout_clicked\0"
    "Button_nextimg_clicked\0Button_previmg_clicked\0"
    "SelectImgFile\0QTreeWidgetItem*\0item\0"
    "col\0SelectLine\0ZoomImage\0f\0on_scroll_h\0"
    "value\0on_scroll_v"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    2,   87,    2, 0x08 /* Private */,
      14,    2,   92,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,
      17,    1,  100,    2, 0x08 /* Private */,
      19,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int,   12,   13,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,

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
        case 8: _t->SelectImgFile((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->SelectLine((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->ZoomImage((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->on_scroll_h((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_scroll_v((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
