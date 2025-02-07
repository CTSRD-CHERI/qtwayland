/****************************************************************************
**
** Copyright (C) 2017 Jolla Ltd, author: <giulio.camuffo@jollamobile.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QSGTexture>
#include <QQuickWindow>
#include <QDebug>

#include "qwaylandquicksurface.h"
#include "qwaylandquickcompositor.h"
#include "qwaylandquickitem.h"
#include <QtWaylandCompositor/qwaylandbufferref.h>
#include <QtWaylandCompositor/QWaylandView>
#include <QtWaylandCompositor/private/qwaylandsurface_p.h>

QT_BEGIN_NAMESPACE

class QWaylandQuickSurfacePrivate : public QWaylandSurfacePrivate
{
    Q_DECLARE_PUBLIC(QWaylandQuickSurface)
public:
    QWaylandQuickSurfacePrivate()
    {
    }

    ~QWaylandQuickSurfacePrivate() override
    {
    }

    bool useTextureAlpha = true;
    bool clientRenderingEnabled = true;
};

QWaylandQuickSurface::QWaylandQuickSurface()
    : QWaylandSurface(* new QWaylandQuickSurfacePrivate())
{

}
QWaylandQuickSurface::QWaylandQuickSurface(QWaylandCompositor *compositor, QWaylandClient *client, quint32 id, int version)
                    : QWaylandSurface(* new QWaylandQuickSurfacePrivate())
{
    initialize(compositor, client, id, version);
}

QWaylandQuickSurface::~QWaylandQuickSurface()
{

}

/*!
 * \qmlproperty bool QtWaylandCompositor::WaylandSurface::useTextureAlpha
 *
 * This property specifies whether the surface should use texture alpha.
 */
bool QWaylandQuickSurface::useTextureAlpha() const
{
    Q_D(const QWaylandQuickSurface);
    return d->useTextureAlpha;
}

void QWaylandQuickSurface::setUseTextureAlpha(bool useTextureAlpha)
{
    Q_D(QWaylandQuickSurface);
    if (d->useTextureAlpha != useTextureAlpha) {
        d->useTextureAlpha = useTextureAlpha;
        emit useTextureAlphaChanged();
        emit configure(d->bufferRef.hasBuffer());
    }
}

/*!
 * \qmlproperty bool QtWaylandCompositor::WaylandSurface::clientRenderingEnabled
 * \deprecated
 *
 * This property used to specify whether client rendering was enabled for the surface.
 * It depended on a Wayland extension that was part of the private API. The surface extension
 * is not used anymore, so this property does nothing.
 */
bool QWaylandQuickSurface::clientRenderingEnabled() const
{
    Q_D(const QWaylandQuickSurface);
    return d->clientRenderingEnabled;
}

void QWaylandQuickSurface::setClientRenderingEnabled(bool enabled)
{
    Q_D(QWaylandQuickSurface);
    qWarning() << Q_FUNC_INFO << "doesn't do anything";
    if (d->clientRenderingEnabled != enabled) {
        d->clientRenderingEnabled = enabled;
        emit clientRenderingEnabledChanged();
    }
}

QT_END_NAMESPACE

#include "moc_qwaylandquicksurface.cpp"
