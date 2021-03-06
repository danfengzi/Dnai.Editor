﻿#ifndef DNAI_MODELS_CONTEXT_MENU_MODEL_H
#define DNAI_MODELS_CONTEXT_MENU_MODEL_H
#include <QAbstractItemModel>
#include <QHash>
#include <QStringList>
#include "generictreeitem.h"
#include "core.h"

namespace dnai
{
	namespace models
	{
        class Entity;
		class ContextMenuItem : public GenericTreeItem<ContextMenuItem>
		{
			Q_OBJECT
			Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
			Q_PROPERTY(int instructionId READ instructionId WRITE setInstructionId NOTIFY instructionIdChanged)
			Q_PROPERTY(QString nodeName READ nodeName WRITE setNodeName NOTIFY nodeNameChanged)
            Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
            Q_PROPERTY(QList<qint32> construction READ construction WRITE setConstruction NOTIFY constructionChanged)
            Q_PROPERTY(int flowIn READ flowIn WRITE setFlowIn NOTIFY flowInChanged)
            Q_PROPERTY(int flowOut READ flowOut WRITE setFlowOut NOTIFY flowOutChanged)
            Q_PROPERTY(int inputSize READ inputSize NOTIFY inputSizeChanged)
            Q_PROPERTY(int outputSize READ outputSize NOTIFY outputSizeChanged)
            Q_PROPERTY(QStringList inputNames READ inputNames NOTIFY inputNamesChanged)
            Q_PROPERTY(QStringList outputNames READ outputNames NOTIFY outputNamesChanged)

        public:
            ContextMenuItem(ContextMenuItem *parent = nullptr);

		public:
			const QString &name() const;
			const QString &description() const;
            const QMap<QString, QString> &inputs() const;
            const QMap<QString, QString> &inputsDisplayNames() const;
            int inputSize() const;
            const QMap<QString, QString> &outputs() const;
            const QMap<QString, QString> &outputsDisplayNames() const;
            int outputSize() const;
			int instructionId() const;
			const QString &nodeName() const;
			int columnCount() const override;
            int type() const;
            QList<qint32> const &construction() const;
            int flowIn() const;
            int flowOut() const;
            QStringList inputNames() const;
            QStringList outputNames() const;
            Q_INVOKABLE QString getInput(QString name) const;
            Q_INVOKABLE QString getOutput(QString name) const;
            Q_INVOKABLE QString getInputDisplayName(QString name) const;
            Q_INVOKABLE QString getOutputDisplayName(QString name) const;
            QString fullPath() const;

		public:
			void setName(const QString &);
            void setDescription(const QString &);
			void setInstructionId(int);
			void setNodeName(const QString &name);
            void setType(int t);
            void setConstruction(QList<qint32> const &value);
            void setFlowIn(int value);
            void setFlowOut(int value);
            void addInput(const QString &name, const QString &type, const QString &displayName);
            void addInputs(const QMap<QString, QString> &inputs, const QMap<QString, QString> &displayNames);
            void addOutput(const QString &name, const QString &type, const QString &displayName);
            void addOutputs(const QMap<QString, QString> &outputs, const QMap<QString, QString> &displayNames);

		signals:
			void nameChanged(const QString &);
            void descriptionChanged(const QString &);
			void instructionIdChanged(int);
			void nodeNameChanged(const QString &name);
            void typeChanged(int t);
            void constructionChanged(QList<qint32> const &value);
            void flowInChanged(int value);
            void flowOutChanged(int value);
            void inputSizeChanged(int value);
            void outputSizeChanged(int value);
			void inputNamesChanged(const QStringList &value);
			void outputNamesChanged(const QStringList &value);

		private:
			QString m_name;
            QString m_descrition;
            int m_instructionId = -1;
			QString m_nodeName;
            int m_type = -1;
            QList<qint32> m_construction;
			int m_flowIn = 0;
			int m_flowOut = 0;

            QMap<QString, QString> m_inputs;
            QMap<QString, QString> m_inputDisplayNames;

            QMap<QString, QString> m_outputs;
            QMap<QString, QString> m_outputDisplayNames;
		};
		class ContextMenuModel : public QAbstractItemModel
		{
			Q_OBJECT
		public:
			enum ROLES
			{
				NAME = Qt::UserRole + 1,
				ITEM,
				DESCRIPTION,
				INPUTS,
                OUTPUTS,
                CONSTRUCTION,
                INSTRUCTION_ID,
                TYPE
			};

		public:
			explicit ContextMenuModel(QObject *parent = nullptr);
			explicit ContextMenuModel(const QJsonObject &doc, QObject *parent = nullptr);

			QModelIndex index(int row, int column, const QModelIndex& parent) const override;
			QModelIndex parent(const QModelIndex& child) const override;
			ContextMenuItem* getItem(const QModelIndex& index) const;
			int rowCount(const QModelIndex& parent) const override;
			int columnCount(const QModelIndex& parent) const override;
			QVariant data(const QModelIndex& index, int role) const override;
            QHash<int, QByteArray> roleNames() const override;

            const QHash<QString, ContextMenuItem*> &instructions() const;

        private:
            void appendVariable(Entity *entity);
            void appendEnumeration(Entity *entity);
            void appendParameter(Entity *entity);
            void appendReturn(Entity *entity);
            void appendObject(Entity *entity);
            void appendList(Entity *entity);
            void appendFunction(Entity *entity);

        private:
            void addItem(ContextMenuItem *item, ContextMenuItem *parent, models::Entity *related = nullptr);
            void addItems(models::Entity *related);
            void removeItem(QString const &fullPath);
            void clearItems(models::Entity *related);
            void refreshItems(models::Entity *related);

        public:
            void setup();

        public slots:
            void onEntityDeclared(dnai::models::Entity *declared);
            void onEntityRemoved(dnai::models::Entity *removed);
            void onEntityRenamed(dnai::models::Entity *entity, QString name, QString newname);
            void onEnumValueSet(dnai::models::Entity *enumeration, QString name, QString value);
            void onEnumValueRemoved(dnai::models::Entity *enumeration, QString name);
            void onObjectAttributeAdded(models::Entity *obj, QString name, models::Entity *type, VISIBILITY visi);
            void onObjectAttributeRenamed(models::Entity *obj, QString name, QString newName);
            void onObjectAttributeRemoved(models::Entity *obj, QString name);
            void onListTypeSet(dnai::models::Entity *lst, dnai::models::Entity *type);
            void onParameterSet(dnai::models::Entity *func, QString param);
            void onReturnSet(dnai::models::Entity *func, QString ret);
            void onVariableTypeSet(dnai::models::Entity *var, dnai::models::Entity *type);

		private:
			void parseJsonDocument(const QJsonObject &json);
			void parseJsonObj(ContextMenuItem* parent, const QJsonObject& js);
			ContextMenuItem *m_root;

            ContextMenuItem *m_functions;
            ContextMenuItem *m_lists;
            ContextMenuItem *m_classes;
            ContextMenuItem *m_variables;
            ContextMenuItem *m_enumerations;

            bool m_functionRebuilding;

            QHash<QString, ContextMenuItem*> m_hash;

        private:
            QHash<models::Entity *, QList<QString>> m_entity_items;
            QHash<QString, models::Entity *> m_items_entity;
		};
	}
}

#endif //DNAI_MODELS_CONTEXT_MENU_MODEL_H
