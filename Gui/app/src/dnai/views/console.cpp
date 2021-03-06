#include "dnai/views/console.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
	namespace views
	{
        Console::Console(QQuickItem* parent) : QQuickItem(parent)
		{
            commands::CommandManager::Instance()->setConsoleView(this);
        }

		void Console::setMode(ConsoleMode mode)
		{
			if (mode == m_mode)
				return;
			m_mode = mode;
			emit modeChanged(mode);
		}

		void Console::addText(const QString& text)
		{
			if (m_text.size() > 10)
				m_text.removeFirst();
			m_text.append(text);
			emit textChanged(m_text);
		}

		void Console::setText(const QStringList& text)
        {
			m_text = text;
			emit textChanged(m_text);
		}
	}
}
