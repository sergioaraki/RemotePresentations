import bb.cascades 1.0
import Network.Request 1.0
import timer 1.0
import bb.system 1.0

Page {
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                configSheet.open();
            }
        }
    }
    titleBar: TitleBar {
        title: "Remote"
    }
    property int segundos
    property string baseurl
    function formatTime(secs){
        var hours   = Math.floor(secs / 3600);
        var minutes = Math.floor((secs - (hours * 3600)) / 60);
        var seconds = secs - (hours * 3600) - (minutes * 60);
        
        if (hours   < 10) {hours   = "0"+hours;}
        if (minutes < 10) {minutes = "0"+minutes;}
        if (seconds < 10) {seconds = "0"+seconds;}
        var time    = hours+':'+minutes+':'+seconds;
        return time;
    }
    Container {
        topPadding: 20
        leftPadding: 20
        rightPadding: 20
        bottomPadding: 20
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        Container {
            layout: StackLayout {
            }
            Container {
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                layout: DockLayout {
                }
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    Label {
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1
                        }
                        id: lTime
                        text: formatTime(segundos)
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        textStyle.fontSize: FontSize.XXLarge
                    }
                    Button {
                        id: bTime
                        property int flag: 0
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1
                        }
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Center
                        text: qsTr("start")
                        imageSource: "images/clock_on.png"
                        onClicked: {
                            if (flag == 0){
                            	bTime.imageSource = "images/clock_off.png"
                                bTime.text = qsTr("stop");
                                timer.start(); 
                                bTime.flag = 1;
                            }
                            else if (flag == 1) {
                                bTime.imageSource = "images/clock_on.png"
                                bTime.text = qsTr("start");
                                timer.stop();
                                bTime.flag = 0;
                            }
                            else if (flag == 2) {
                                bTime.imageSource = "images/clock_on.png"
                                bTime.text = qsTr("start");
                                segundos=app.getDuration()*60;
                                lTime.setText(formatTime(segundos));
                                lTime.textStyle.color = Color.White
                                bTime.flag = 0;
                            }	
                        }
                    }
                    contextActions: [
                        ActionSet {
                            ActionItem {
                                title: qsTr("reset")
                                imageSource: "asset:///images/clock.png"
                                onTriggered: {
                                    timer.stop();
                                    bTime.imageSource = "images/clock_on.png"
                                    bTime.text = qsTr("start");
                                    segundos=app.getDuration()*60;
                                    lTime.setText(formatTime(segundos));
                                    lTime.textStyle.color = Color.White
                                    bTime.flag = 0;
                                }
                            }
                        }
                    ]
                }
            }
            Container {
                layout: DockLayout {
                }
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Center
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        id: prev
                        text: qsTr("previous")
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1
                        }
                        onClicked: {
                            requestPrev.getRequest(baseurl+"/prev.html");
                        }
                    }
                    Button {
                        id: next
                        text: qsTr("next")
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1
                        }
                        onClicked: {
                            requestNext.getRequest(baseurl+"/next.html");
                        }
                    }
                }
            }
        }
    }
    attachedObjects: [
        Request {
            id: requestNext
            onComplete: {
                if (info === 0) {
                    toastSC.show();
                }
                else {
                    console.log("Next");
                }
            }
        },
        Request {
            id: requestPrev
            onComplete: {
                if (info === 0) {
                    toastSC.show();
                }
                else {
                    console.log("Prev");
                }
            }
        },
        SystemToast {
            id: toastSC
            body: qsTr("error")
        },
        QTimer{
            id: timer
            interval: 1000
            onTimeout:{
                segundos = segundos - 1
                if (segundos<900 && segundos>300){
                    lTime.textStyle.color = Color.Yellow
                }    
                else if (segundos<300 && segundos>0){
                    lTime.textStyle.color = Color.Red
                }    
                else if (segundos==0) {
                    timer.stop();
                    bTime.imageSource = "images/clock.png"
                    bTime.text = qsTr("reset");
                    bTime.flag = 2;
                }
            }
        },
        Sheet {
            id: configSheet
            content: Config{
            }
        }
    ]
    onCreationCompleted: {
        Application.mainWindow.screenIdleMode = 1;
        baseurl=app.getServer();
        segundos=app.getDuration()*60;
        lTime.setText(formatTime(segundos));
    }
}