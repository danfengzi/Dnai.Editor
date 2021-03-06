#ifndef MOVECANVASCOMMAND_H
#define MOVECANVASCOMMAND_H

#include "command.h"
#include "dnai/views/canvasnode.h"

namespace dnai
{
    namespace commands
    {
        class MoveCanvasCommand : public Command
        {
        public:
                MoveCanvasCommand(views::CanvasNode* canvas, const QPointF& pos, bool save);
            /**
            * \brief Execute the command
            */
            void execute() const override;
            void executeSave() override;

            /**
            * \brief Reverse the command
            */
            void unExcute() const override;

            QString infos() const override;

        private:
            QPointF m_pos;
            QPointF m_lastPos;
            views::CanvasNode* m_canvas;
        };
    }
}

#endif // MOVECANVASCOMMAND_H
