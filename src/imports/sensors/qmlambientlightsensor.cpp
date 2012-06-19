/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qmlambientlightsensor.h"
#include <QAmbientLightSensor>

/*!
    \qmltype AmbientLightSensor
    \instantiates QmlAmbientLightSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.1
    \inherits QtMobility.sensors1::Sensor
    \brief The AmbientLightSensor element repors on ambient lighting conditions.

    The AmbientLightSensor element repors on ambient lighting conditions.

    This element wraps the QAmbientLightSensor class. Please see the documentation for
    QAmbientLightSensor for details.

    \sa AmbientLightReading
*/

QmlAmbientLightSensor::QmlAmbientLightSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QAmbientLightSensor(this))
{
}

QmlAmbientLightSensor::~QmlAmbientLightSensor()
{
}

QmlSensorReading *QmlAmbientLightSensor::createReading() const
{
    return new QmlAmbientLightSensorReading(m_sensor);
}

QSensor *QmlAmbientLightSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype AmbientLightReading
    \instantiates QmlAmbientLightSensorReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.1
    \inherits QtMobility.sensors1::SensorReading
    \brief The AmbientLightReading element holds the most AmbientLightSensor reading.

    The AmbientLightReading element holds the most AmbientLightSensor reading.

    This element wraps the QAmbientLightReading class. Please see the documentation for
    QAmbientLightReading for details.

    This element cannot be directly created.
*/

QmlAmbientLightSensorReading::QmlAmbientLightSensorReading(QAmbientLightSensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
{
}

QmlAmbientLightSensorReading::~QmlAmbientLightSensorReading()
{
}

/*!
    \qmlproperty LightLevel QtMobility.sensors1::AmbientLightReading::lightLevel
    This property holds the ambient light level.

    Please see QAmbientLightReading::lightLevel for information about this property.

    Note that LightLevel constants are exposed through the AmbientLightReading class.
    \code
        AmbientLightSensor {
            onReadingChanged: {
                if (reading.lightLevel == AmbientLightReading.Dark)
                    // do something
            }
        }
    \endcode
*/

QAmbientLightReading::LightLevel QmlAmbientLightSensorReading::lightLevel() const
{
    return m_lightLevel;
}

QSensorReading *QmlAmbientLightSensorReading::reading() const
{
    return m_sensor->reading();
}

void QmlAmbientLightSensorReading::readingUpdate()
{
    QAmbientLightReading::LightLevel ll = m_sensor->reading()->lightLevel();
    if (m_lightLevel != ll) {
        m_lightLevel = ll;
        Q_EMIT lightLevelChanged();
    }
}
