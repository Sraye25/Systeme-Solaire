#ifndef __OPENGLWINDOW_H__
#define __OPENGLWINDOW_H__

#include <QtGui/QWindow>
#include <QOpenGLFunctions_3_3_Core>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE


class OpenGLWindow : public QWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
    public:
        explicit OpenGLWindow(QWindow *parent = 0);
        ~OpenGLWindow();

        virtual void render(QPainter *painter);
        virtual void render();
        virtual void update() = 0;

        virtual void initialize();

        void setAnimating(bool animating);

    public slots:
        void renderLater();
        void renderNow();

    protected:

        inline bool isInitialized() const;

        bool event(QEvent *event) Q_DECL_OVERRIDE;

        void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

    private:
        bool                    m_update_pending;
        bool                    m_animating;

        QOpenGLContext*         m_context;
        QOpenGLPaintDevice*     m_device;
};

//====================================================================================================================================
bool OpenGLWindow::isInitialized() const
{
    return 0 != m_context;
}
#endif //__OPENGLWINDOW_H__
