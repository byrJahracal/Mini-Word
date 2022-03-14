/****************************************************************************
** Meta object code from reading C++ file 'miniword.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../miniword.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'miniword.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MiniWord_t {
    QByteArrayData data[15];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MiniWord_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MiniWord_t qt_meta_stringdata_MiniWord = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MiniWord"
QT_MOC_LITERAL(1, 9, 27), // "on_action_newFile_triggered"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 28), // "on_action_openfile_triggered"
QT_MOC_LITERAL(4, 67, 24), // "on_action_quit_triggered"
QT_MOC_LITERAL(5, 92, 28), // "on_action_savefile_triggered"
QT_MOC_LITERAL(6, 121, 26), // "on_action_search_triggered"
QT_MOC_LITERAL(7, 148, 27), // "on_action_replace_triggered"
QT_MOC_LITERAL(8, 176, 27), // "on_action_save_as_triggered"
QT_MOC_LITERAL(9, 204, 21), // "receiveData_to_search"
QT_MOC_LITERAL(10, 226, 22), // "receiveData_to_replace"
QT_MOC_LITERAL(11, 249, 26), // "receiveData_to_replace_all"
QT_MOC_LITERAL(12, 276, 10), // "cur_p_show"
QT_MOC_LITERAL(13, 287, 27), // "on_action_addsize_triggered"
QT_MOC_LITERAL(14, 315, 27) // "on_action_cutsize_triggered"

    },
    "MiniWord\0on_action_newFile_triggered\0"
    "\0on_action_openfile_triggered\0"
    "on_action_quit_triggered\0"
    "on_action_savefile_triggered\0"
    "on_action_search_triggered\0"
    "on_action_replace_triggered\0"
    "on_action_save_as_triggered\0"
    "receiveData_to_search\0receiveData_to_replace\0"
    "receiveData_to_replace_all\0cur_p_show\0"
    "on_action_addsize_triggered\0"
    "on_action_cutsize_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MiniWord[] = {

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
       9,    1,   86,    2, 0x08 /* Private */,
      10,    2,   89,    2, 0x08 /* Private */,
      11,    2,   94,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MiniWord::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MiniWord *_t = static_cast<MiniWord *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_action_newFile_triggered(); break;
        case 1: _t->on_action_openfile_triggered(); break;
        case 2: _t->on_action_quit_triggered(); break;
        case 3: _t->on_action_savefile_triggered(); break;
        case 4: _t->on_action_search_triggered(); break;
        case 5: _t->on_action_replace_triggered(); break;
        case 6: _t->on_action_save_as_triggered(); break;
        case 7: _t->receiveData_to_search((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->receiveData_to_replace((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->receiveData_to_replace_all((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->cur_p_show(); break;
        case 11: _t->on_action_addsize_triggered(); break;
        case 12: _t->on_action_cutsize_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject MiniWord::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MiniWord.data,
      qt_meta_data_MiniWord,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MiniWord::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MiniWord::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MiniWord.stringdata0))
        return static_cast<void*>(const_cast< MiniWord*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MiniWord::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
