/*
 *   Copyright 2007 Richard J. Moore <rich@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QUrl>
#include "backportglobal.h"

Q_DECLARE_METATYPE(QUrl*)

static QScriptValue urlCtor(QScriptContext *ctx, QScriptEngine *eng)
{
    if (ctx->argumentCount() == 1)
    {
        QString url = ctx->argument(0).toString();
        return qScriptValueFromValue(eng, QUrl(url));
    }

    return qScriptValueFromValue(eng, QUrl());
}

static QScriptValue toString(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QUrl, toString);
    return QScriptValue(eng, self->toString());
}

static QScriptValue protocol(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QUrl, protocol);
    if (ctx->argumentCount()) {
        QString v = ctx->argument(0).toString();
        self->setScheme(v);
    }

    return QScriptValue(eng, self->scheme());
}

static QScriptValue host(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QUrl, protocol);
    if (ctx->argumentCount()) {
        QString v = ctx->argument(0).toString();
        self->setHost(v);
    }

    return QScriptValue(eng, self->host());
}

static QScriptValue path(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QUrl, path);
    if (ctx->argumentCount()) {
        QString v = ctx->argument(0).toString();
        self->setPath(v);
    }

    return QScriptValue(eng, self->path());
}

static QScriptValue user(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QUrl, user);
    if (ctx->argumentCount()) {
        QString v = ctx->argument(0).toString();
        self->setUserName(v);
    }

    return QScriptValue(eng, self->userName());
}

static QScriptValue password(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QUrl, password);
    if (ctx->argumentCount()) {
        QString v = ctx->argument(0).toString();
        self->setPassword(v);
    }

    return QScriptValue(eng, self->password());
}

QScriptValue constructQUrlClass(QScriptEngine *eng)
{
    QScriptValue proto = qScriptValueFromValue(eng, QUrl());
    QScriptValue::PropertyFlags getter = QScriptValue::PropertyGetter;
    QScriptValue::PropertyFlags setter = QScriptValue::PropertySetter;

    proto.setProperty(QStringLiteral("toString"), eng->newFunction(toString), getter);
    proto.setProperty(QStringLiteral("protocol"), eng->newFunction(protocol), getter | setter);
    proto.setProperty(QStringLiteral("host"), eng->newFunction(host), getter | setter);
    proto.setProperty(QStringLiteral("path"), eng->newFunction(path), getter | setter);
    proto.setProperty(QStringLiteral("user"), eng->newFunction(user), getter | setter);
    proto.setProperty(QStringLiteral("password"), eng->newFunction(password), getter | setter);

    eng->setDefaultPrototype(qMetaTypeId<QUrl*>(), proto);
    eng->setDefaultPrototype(qMetaTypeId<QUrl>(), proto);

    return eng->newFunction(urlCtor, proto);
}