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

#include <time.h>
// #include <QUrlQuery>
#include <QCryptographicHash>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QFile>
#include <string>
#include "upyun_client_impl.h"
#include <clocale>

QString g_upyun_api_host = "http://v0.api.upyun.com";

std::string rfc1123_datetime(time_t time) {
	struct tm * timeinfo;
	char buffer[80];

	std::setlocale(LC_ALL, "en_US.UTF-8");
	timeinfo = gmtime(&time);
	strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeinfo);

	return buffer;
}

QString get_sign(const QString &method, const QString &path_url,
		const QString &now_time, const QString &content_len,
		const QString &pwd) {
	if (QString("") == content_len)
		throw QString("Content-Len in sign is '', maybe '0'?");

	QString linkstr = method + "&" + path_url + "&" + now_time + "&"
			+ content_len;

	QString pwd_hash = QCryptographicHash::hash(pwd.toUtf8(),
			QCryptographicHash::Md5).toHex();

	linkstr += "&" + pwd_hash;

	return QCryptographicHash::hash(linkstr.toUtf8(), QCryptographicHash::Md5).toHex();
}

QString get_auth_string(const QString &usr, const QString &sign) {
	QString auth = "UpYun " + usr + ":";
	auth.append(sign);
	return auth;
}

UpyunClientPrivate::UpyunClientPrivate(const QString &usr, const QString &pass,
		const QString &bucket, QObject *parent) :
		_usr(usr), _pwd(pass), _bucket(bucket), QObject(parent) {

}

QNetworkReply* UpyunClientPrivate::uploadFile(const QByteArray &filedata,
		const QString &remote_path) {
	QString content_len = QString::number(filedata.length());
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();

	QString auth = get_auth_string(_usr,
			get_sign("PUT", path_url, now_time, content_len, _pwd));

	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Content-Length", content_len.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());
	request.setRawHeader("mkdir", "true");

	QNetworkReply *reply = _qnam.put(request, filedata);

	return reply;

}

QNetworkReply* UpyunClientPrivate::downloadFile(const QString &remote_path) {
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("GET", path_url, now_time, "0", _pwd));
	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());

	QNetworkReply *reply = _qnam.get(request);

	return reply;
}

QNetworkReply *UpyunClientPrivate::removeFile(const QString &remote_path) {
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("DELETE", path_url, now_time, "0", _pwd));

	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());
	request.setRawHeader("mkdir", "true");

	QNetworkReply *reply = _qnam.deleteResource(request);

	return reply;
}

QNetworkReply *UpyunClientPrivate::makeDir(const QString &remote_path) {
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("POST", path_url, now_time, "0", _pwd));
	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Content-Length", "0");
	request.setRawHeader("Content-Type", "text/html");
	request.setRawHeader("Date", now_time.toLatin1());
	request.setRawHeader("folder", "create");
	request.setRawHeader("mkdir", "true");

	QNetworkReply *reply = _qnam.post(request, "");

	return reply;
}

QNetworkReply *UpyunClientPrivate::removeDir(const QString &remote_path) {
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("DELETE", path_url, now_time, "0", _pwd));

	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());

	QNetworkReply *reply = _qnam.deleteResource(request);

	return reply;
}

QNetworkReply *UpyunClientPrivate::listDir(const QString &remote_path) {
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("GET", path_url, now_time, "0", _pwd));

	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());

	QNetworkReply *reply = _qnam.get(request);

	return reply;
}

QNetworkReply *UpyunClientPrivate::getBucketInfo() {
	QString path_url = "/" + _bucket + "/?usage";
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("GET", path_url, now_time, "0", _pwd));

	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());

	QNetworkReply *reply = _qnam.get(request);

	return reply;
}

QNetworkReply *UpyunClientPrivate::getFileInfo(const QString &remote_path) {
	QString path_url = "/" + _bucket + "/" + remote_path;
	QString now_time = rfc1123_datetime(time(NULL)).c_str();
	QString auth = get_auth_string(_usr,
			get_sign("HEAD", path_url, now_time, "0", _pwd));

	// QUrl url = upyun_api_host + path_url;
	QUrl url = QUrl::fromEncoded((g_upyun_api_host + path_url).toLocal8Bit());

	QNetworkRequest request(url);
	request.setRawHeader("Authorization", auth.toLatin1());
	request.setRawHeader("Date", now_time.toLatin1());

	QNetworkReply *reply = _qnam.head(request);

	return reply;
}

