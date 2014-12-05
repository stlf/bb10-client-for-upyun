/*
 * Copyright (c) 2011-2014 stlf@live.cn.
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

#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include <QStringList>

#include "upyun_client.h"
#include "upyun_client_impl.h"

#define HTTP_OK 200
#define HTTP_ABORT -1

UpyunClient::UpyunClient(const QString &usr, const QString &pass,
		const QString &bucket) :
		d_ptr(new UpyunClientPrivate(usr, pass, bucket, this)) {

}

template<typename CT>
int waiting_reply(QNetworkReply *reply, CT *c) {
	QEventLoop loop;

	QObject::connect(c, SIGNAL(notifyStop()), &loop, SLOT(quit()),
			Qt::QueuedConnection);

	bool is_notify_stop = false;

	// QObject::connect(c, SIGNAL(notifyStop()), [&](){is_notify_stop = true;});

	QObject::connect(c, SIGNAL(notifyStop()), &loop, SLOT(quit()));

	QObject::connect(reply, SIGNAL(downloadProgress(qint64,qint64)), c,
			SIGNAL(progress(qint64,qint64)), Qt::UniqueConnection);

	QObject::connect(reply, SIGNAL(uploadProgress(qint64,qint64)), c,
			SIGNAL(progress(qint64,qint64)), Qt::UniqueConnection);

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

	loop.exec();

	if (is_notify_stop)
		return HTTP_ABORT;

	return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

bool check_reply_code(const int code) {
	if (HTTP_OK == code)
		return true;
	if (HTTP_ABORT == code)
		return true;
	return false;
}

void UpyunClient::uploadFile(const QString &local_path,
		const QString &remote_path) {
	QFile file(local_path);
	if (!file.open(QIODevice::ReadOnly)) {
		throw QString("can not open or read file:" + local_path);
	}

	Q_D(UpyunClient);
	QNetworkReply* reply = d->uploadFile(file.readAll(), remote_path);

	if (!check_reply_code(waiting_reply(reply, this)))
	{
        reply->abort();
        reply->deleteLater();
		throw QString(reply->errorString());
	}

}

QByteArray UpyunClient::downloadFile(const QString &remote_path) {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->downloadFile(remote_path);
	if (!check_reply_code(waiting_reply(reply, this)))
	{
	    reply->abort();
        reply->deleteLater();
		throw QString(reply->errorString());
	}

	return reply->readAll();
}

void UpyunClient::removeFile(const QString &remote_path) {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->removeFile(remote_path);
	if (!check_reply_code(waiting_reply(reply, this)))
		throw QString(reply->errorString());
}

void UpyunClient::makeDir(const QString &remote_path) {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->makeDir(remote_path);
	if (!check_reply_code(waiting_reply(reply, this)))
		throw QString(reply->errorString() + ":" + remote_path);
}

void UpyunClient::removeDir(const QString &remote_path) {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->removeDir(remote_path);
	if (!check_reply_code(waiting_reply(reply, this)))
		throw QString(reply->errorString());
}

QList<upyun_file_info> UpyunClient::listDir(const QString &remote_path) {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->listDir(remote_path);
	if (!check_reply_code(waiting_reply(reply, this)))
		throw QString(reply->errorString());

	const QString &info = QString::fromUtf8(reply->readAll());
	const QStringList &file_items = info.split("\n");

	QList<upyun_file_info> file_infos;
	foreach(QString file_item, file_items)
	{
		upyun_file_info fi;

		const QStringList &cols = file_item.split("\t");
		if (cols.size() != 4) {
			continue;
		}
		fi.name = cols[0];
		fi.type = cols[1];
		fi.size = cols[2];
		fi.date = cols[3];

		file_infos.push_back(fi);
	}

	return file_infos;
}

QString UpyunClient::getBucketUsage() {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->getBucketInfo();
	if (!check_reply_code(waiting_reply(reply, this)))
		throw QString(reply->errorString());

	return QString::fromUtf8(reply->readAll());
}

upyun_file_info UpyunClient::getFileInfo(const QString &remote_path) {
	Q_D(UpyunClient);
	QNetworkReply* reply = d->getFileInfo(remote_path);
	if (!check_reply_code(waiting_reply(reply, this)))
		throw QString(reply->errorString());

	upyun_file_info fi;
	QStringList fp = remote_path.split("/");

	int s = fp.size();
	if (s) {
		fi.name = fp[s - 1];
	}

	fi.type = reply->rawHeader("x-upyun-file-type");
	fi.size = reply->rawHeader("x-upyun-file-size");
	fi.date = reply->rawHeader("x-upyun-file-date");

	return fi;
}

