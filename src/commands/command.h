/* -*- mode: c++; c-basic-offset:4 -*-
    commands/command.h

    This file is part of Kleopatra, the KDE keymanager
    SPDX-FileCopyrightText: 2007 Klarälvdalens Datakonsult AB

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include <qwindowdefs.h> // for WId

#include <utils/pimpl_ptr.h>
#include <utils/types.h> // for ExecutionContext

#include <vector>

class QModelIndex;
template <typename T> class QList;
class QAbstractItemView;

namespace GpgME
{
class Key;
}

namespace Kleo
{

class KeyListController;
class AbstractKeyListSortFilterProxyModel;

class Command : public QObject, public ExecutionContext
{
    Q_OBJECT
public:
    explicit Command(KeyListController *parent);
    explicit Command(QAbstractItemView *view, KeyListController *parent);
    explicit Command(const GpgME::Key &key);
    explicit Command(const std::vector<GpgME::Key> &keys);
    ~Command() override;

    enum Restriction {
        NoRestriction      = 0,
        NeedSelection      = 1,
        OnlyOneKey         = 2,
        NeedSecretKey      = 4,
        MustNotBeSecretKey = 8,
        MustBeOpenPGP      = 16,
        MustBeCMS          = 32,

        // esoteric:
        MayOnlyBeSecretKeyIfOwnerTrustIsNotYetUltimate = 64, // for set-owner-trust

        AnyCardHasNullPin   = 128,
        AnyCardCanLearnKeys = 256,

        MustBeRoot          = 512,
        MustBeTrustedRoot   = 1024 | MustBeRoot,
        MustBeUntrustedRoot = 2048 | MustBeRoot,

        _AllRestrictions_Helper,
        AllRestrictions = 2 * (_AllRestrictions_Helper - 1) - 1
    };

    Q_DECLARE_FLAGS(Restrictions, Restriction)

    static Restrictions restrictions()
    {
        return NoRestriction;
    }

    /** Classify the files and return the most appropriate commands.
     *
     * @param files: A list of files.
     *
     * @returns null QString on success. Error message otherwise.
     */
    static QVector<Command *>commandsForFiles(const QStringList &files);

    /** Get a command for a query.
     *
     * @param query: A keyid / fingerprint or any string to use in the search.
     */
    static Command *commandForQuery(const QString &query);

    void setParentWidget(QWidget *widget);
    void setParentWId(WId wid);
    void setView(QAbstractItemView *view);
    void setIndex(const QModelIndex &idx);
    void setIndexes(const QList<QModelIndex> &idx);
    void setKey(const GpgME::Key &key);
    void setKeys(const std::vector<GpgME::Key> &keys);

    void setAutoDelete(bool on);
    bool autoDelete() const;

    void setWarnWhenRunningAtShutdown(bool warn);
    bool warnWhenRunningAtShutdown() const;

public Q_SLOTS:
    void start();
    void cancel();

Q_SIGNALS:
    void info(const QString &message, int timeout = 0);
    void progress(const QString &message, int current, int total);
    void finished();
    void canceled();

private:
    virtual void doStart() = 0;
    virtual void doCancel() = 0;

private:
    void applyWindowID(QWidget *wid) const override;

protected:
    void addTemporaryView(const QString &title, AbstractKeyListSortFilterProxyModel *proxy = nullptr, const QString &tabToolTip = QString());

protected:
    class Private;
    kdtools::pimpl_ptr<Private> d;
protected:
    explicit Command(Private *pp);
    explicit Command(QAbstractItemView *view, Private *pp);
    explicit Command(const std::vector<GpgME::Key> &keys, Private *pp);
    explicit Command(const GpgME::Key &key, Private *pp);
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(Kleo::Command::Restrictions)

