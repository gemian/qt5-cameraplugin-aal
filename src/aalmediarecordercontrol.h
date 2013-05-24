/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AALMEDIARECORDERCONTROL_H
#define AALMEDIARECORDERCONTROL_H

#include <QMediaRecorderControl>
#include <QUrl>

#include <stdint.h>

class AalCameraService;
struct MediaRecorderWrapper;
class QTimer;

class AalMediaRecorderControl : public QMediaRecorderControl
{
Q_OBJECT
public:
    AalMediaRecorderControl(AalCameraService *service, QObject *parent = 0);
    ~AalMediaRecorderControl();

    virtual void applySettings();
    virtual qint64 duration() const;
    virtual bool isMuted() const;
    virtual QUrl outputLocation() const;
    virtual bool setOutputLocation(const QUrl & location);
    virtual QMediaRecorder::State state() const;
    virtual QMediaRecorder::Status status() const;
    virtual qreal volume() const;

    void init();
    void deleteRecorder();

    static void errorCB(void* context);

public Q_SLOTS:
    virtual void setMuted(bool muted);
    virtual void setState(QMediaRecorder::State state);
    virtual void setVolume(qreal gain);

private Q_SLOTS:
    virtual void updateDuration();
    void handleError();

private:
    void setStatus(QMediaRecorder::Status status);
    int startRecording();
    void stopRecording();

    AalCameraService *m_service;
    MediaRecorderWrapper *m_mediaRecorder;
    QUrl m_outputLocation;
    qint64 m_duration;
    QMediaRecorder::State m_currentState;
    QMediaRecorder::Status m_currentStatus;
    QTimer *m_recordingTimer;
};

#endif
