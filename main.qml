import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: "Integrated Camera and Motion Controller"

    // Global properties for easier access
    property string cameraIp: "192.168.1.188"
    property string motionIp: "192.168.0.11"
    property double targetPosition: 1000.0

    // --- Main Layout ---
    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        // =================================================================
        // Camera Control Column
        // =================================================================
        GroupBox {
            title: "Camera Control"
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                width: parent.width

                // --- Connection ---
                RowLayout {
                    TextField {
                        id: cameraIpField
                        text: cameraIp
                        placeholderText: "Camera IP"
                        Layout.fillWidth: true
                        onAccepted: cameraIp = text
                    }
                    Button {
                        id: cameraConnectButton
                        text: cameraManager.isConnected ? "Disconnect" : "Connect"
                        onClicked: {
                            if (cameraManager.isConnected) {
                                cameraManager.disconnectDevice()
                            } else {
                                cameraManager.connectDevice(cameraIpField.text)
                            }
                        }
                    }
                }

                // --- Controls ---
                GroupBox {
                    title: "Live Controls"
                    enabled: cameraManager.isConnected
                    Layout.fillWidth: true

                    GridLayout {
                        columns: 2
                        width: parent.width

                        Label { text: "Exposure (us):" }
                        Slider {
                            id: exposureSlider
                            from: 10
                            to: 10000
                            value: 500
                            Layout.fillWidth: true
                            onMoved: cameraManager.setExposure(value)
                        }

                        Button {
                            text: "Start Capture"
                            onClicked: cameraManager.startCapture()
                            Layout.fillWidth: true
                        }
                        Button {
                            text: "Stop Capture"
                            onClicked: cameraManager.stopCapture()
                            Layout.fillWidth: true
                        }
                    }
                }

                // --- Status ---
                Label {
                    id: cameraStatusLabel
                    text: "Status: " + cameraManager.statusMessage
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }


        // =================================================================
        // Motion Control Column
        // =================================================================
        GroupBox {
            title: "Motion Control (Axis 0)"
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                width: parent.width

                // --- Connection ---
                RowLayout {
                    TextField {
                        id: motionIpField
                        text: motionIp
                        placeholderText: "Motion Controller IP"
                        Layout.fillWidth: true
                        onAccepted: motionIp = text
                    }
                    Button {
                        id: motionConnectButton
                        text: motionManager.isConnected ? "Disconnect" : "Connect"
                        onClicked: {
                            if (motionManager.isConnected) {
                                motionManager.disconnectDevice()
                            } else {
                                motionManager.connectDevice(motionIpField.text)
                            }
                        }
                    }
                }

                // --- Controls ---
                GroupBox {
                    title: "Movement"
                    enabled: motionManager.isConnected
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width

                        Button {
                            text: "Enable Axis"
                            onClicked: motionManager.enableAxis(0)
                            Layout.fillWidth: true
                        }

                        RowLayout {
                            Label { text: "Target Pos:" }
                            TextField {
                                id: targetPosField
                                text: targetPosition.toString()
                                validator: DoubleValidator {}
                                onAccepted: targetPosition = Number(text)
                                Layout.fillWidth: true
                            }
                        }

                        Button {
                            text: "Move Absolute"
                            onClicked: motionManager.moveAbsolute(0, targetPosition)
                            Layout.fillWidth: true
                        }

                        RowLayout {
                            Label { text: "Jog:"}
                            Button {
                                text: "Reverse (-)"
                                onClicked: motionManager.jog(0, -1)
                                Layout.fillWidth: true
                            }
                            Button {
                                text: "Forward (+)"
                                onClicked: motionManager.jog(0, 1)
                                Layout.fillWidth: true
                            }
                            Button {
                                text: "Stop"
                                onClicked: motionManager.stop(0)
                            }
                        }
                    }
                }

                // --- Status ---
                Label {
                    text: "Position: " + motionManager.currentPosition.toFixed(3)
                }
                Label {
                    id: motionStatusLabel
                    text: "Status: " + motionManager.statusMessage
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }
    }
}
