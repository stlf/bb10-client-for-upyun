/*
 * Copyright (c) 2011-2014 stlf@live.cn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UPYUN_CLIENT_IMPL_H
#define UPYUN_CLIENT_IMPL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class UpyunClientPrivate : public QObject
{
    Q_OBJECT
public:
    explicit UpyunClientPrivate(const QString &usr, const QString &pass, const QString &bucket,
                               QObject *parent = 0);
signals:
    void error(const QString &info);

public slots:
    QNetworkReply *uploadFile(const QByteArray &filedata, const QString &remote_path);
    QNetworkReply *downloadFile(const QString &remote_path);

    QNetworkReply *removeFile(const QString &remote_path);
    QNetworkReply *makeDir(const QString &remote_path);
    QNetworkReply *removeDir(const QString &remote_path);
    QNetworkReply *listDir(const QString &remote_path);

    QNetworkReply *getBucketInfo();
    QNetworkReply *getFileInfo(const QString &remote_path);

private:
    QString _usr;
    QString _pwd;
    QString _bucket;

    QNetworkAccessManager _qnam;

};


#endif // UPYUN_CLIENT_IMPL_H
