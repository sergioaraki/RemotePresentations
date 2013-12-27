/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
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

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
	//add custom object Request class as a qml type
	qmlRegisterType<Request>("Network.Request", 1, 0, "Request");
	qmlRegisterType<QTimer>("timer", 1, 0, "QTimer");
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("app", this);
    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("Remote_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

int ApplicationUI::getDuration(){
	QSettings settings;

	if (settings.value("ar.com.sergioaraki.remote.duration").isNull()) {
		return 60;
	}

	return settings.value("ar.com.sergioaraki.remote.duration").toInt();
}

void ApplicationUI::setDuration(const int &value){
	QSettings settings;
	settings.setValue("ar.com.sergioaraki.remote.duration", QVariant(value));
}

QString ApplicationUI::getServer(){
	QSettings settings;

	if (settings.value("ar.com.sergioaraki.remote.server").isNull()) {
		return "http://192.168.1.100:8080";
	}

	return settings.value("ar.com.sergioaraki.remote.server").toString();
}

void ApplicationUI::setServer(const QString &value){
	QSettings settings;
	settings.setValue("ar.com.sergioaraki.remote.server", QVariant(value));
}
