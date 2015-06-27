/****************************************************************************
** Meta object code from reading C++ file 'upyun_client_impl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/upyun_client_impl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upyun_client_impl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpyunClientPrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   55,   40,   19, 0x0a,
     119,  107,   40,   19, 0x0a,
     141,  107,   40,   19, 0x0a,
     161,  107,   40,   19, 0x0a,
     178,  107,   40,   19, 0x0a,
     197,  107,   40,   19, 0x0a,
     214,   19,   40,   19, 0x0a,
     230,  107,   40,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UpyunClientPrivate[] = {
    "UpyunClientPrivate\0\0info\0error(QString)\0"
    "QNetworkReply*\0filedata,remote_path\0"
    "uploadFile(QByteArray,QString)\0"
    "remote_path\0downloadFile(QString)\0"
    "removeFile(QString)\0makeDir(QString)\0"
    "removeDir(QString)\0listDir(QString)\0"
    "getBucketInfo()\0getFileInfo(QString)\0"
};

void UpyunClientPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpyunClientPrivate *_t = static_cast<UpyunClientPrivate *>(_o);
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: { QNetworkReply* _r = _t->uploadFile((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 2: { QNetworkReply* _r = _t->downloadFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 3: { QNetworkReply* _r = _t->removeFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 4: { QNetworkReply* _r = _t->makeDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 5: { QNetworkReply* _r = _t->removeDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 6: { QNetworkReply* _r = _t->listDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 7: { QNetworkReply* _r = _t->getBucketInfo();
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 8: { QNetworkReply* _r = _t->getFileInfo((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UpyunClientPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UpyunClientPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UpyunClientPrivate,
      qt_meta_data_UpyunClientPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UpyunClientPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UpyunClientPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UpyunClientPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpyunClientPrivate))
        return static_cast<void*>(const_cast< UpyunClientPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int UpyunClientPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void UpyunClientPrivate::error(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
