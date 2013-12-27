import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("config")
        acceptAction: ActionItem {
            title: "Ok"
            onTriggered: {
                configSheet.close();
            }
        }
    }
    Container {
        topPadding: 20
        leftPadding: 20
        rightPadding: 20
        layout: StackLayout {
        }
        horizontalAlignment: HorizontalAlignment.Fill
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            horizontalAlignment: HorizontalAlignment.Fill
            Label {
                text: qsTr("server")
            }
            TextField {
                id: server
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                horizontalAlignment: HorizontalAlignment.Fill
                onTextChanged: {
                    app.setServer(text);
                }
            }
        }
        Container {
            topPadding: 10
	        layout: StackLayout {
	            orientation: LayoutOrientation.LeftToRight
	        }
            horizontalAlignment: HorizontalAlignment.Fill
	        Label {
                text: qsTr("duration")
	            layoutProperties: StackLayoutProperties {
	                spaceQuota: 1
	            }
	        }
	        TextField {
	            id: duration
	            layoutProperties: StackLayoutProperties {
	                spaceQuota: 1
	            }
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            horizontalAlignment: HorizontalAlignment.Fill
	            onTextChanged: {
	                app.setDuration(text);
	            }
	        }
        }
    }
    onCreationCompleted: {
        duration.text=app.getDuration();
        server.text=app.getServer();
    }
}
