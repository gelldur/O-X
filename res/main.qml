import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

import com.GameController 1.0

ApplicationWindow {
    visible: true
    property int margin: 90
    property int minSize:360
    minimumWidth: minSize + 2 * margin
    minimumHeight: minSize + 2 * margin
    maximumWidth: minSize * 4
    maximumHeight: minSize * 4

    width: minimumWidth
    height: minimumHeight

    color: "#efda64"

    title: qsTr("Noughts and Crosses")

//    tools: ToolbarActions {
//        id: toolbar
//        active: true

//        Action {
//            text: "New Game"
//            onTriggered: game.newGame()
//        }
//    }

    GameController {
           id: gameController
    }

    function getX(index)
    {
        return index / gameBoard.boardSize
    }

    function getY(index)
    {
        return (gameBoard.boardSize - index % gameBoard.boardSize)-1
    }

    function updateView()
    {
        for (var i = 0; i < gridRepeater.count; ++i)
        {
            gridRepeater.itemAt(i).state = String.fromCharCode(gameController.getField(getX(i),getY(i)));
        }

        message.text = gameController.getInformation();

        actionButton.text = gameController.actionButtonText();

        playerA.text = gameController.getPlayerAText();
        playerB.text = gameController.getPlayerBText();
    }

    Component.onCompleted: {
        updateView();
    }

    Label {
        id: playerA
        anchors {
            bottom: parent.bottom; bottomMargin: 10
            left: parent.left; leftMargin: 10
        }

        text: "XXX"
    }

    Label {
        id: playerB
        anchors {
            bottom: parent.bottom; bottomMargin:10
            right: parent.right; rightMargin:10
        }

        text: "YYYY"
    }

    Label {
        id: message
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top; topMargin:10
        }

        text: "XYZ"
        font.pointSize: 18
    }

    GridLayout {
        id: gameBoard
        property int boardSize: 3
        property int spacing: 10

        rows: boardSize
        columns: boardSize
        flow: GridLayout.TopToBottom
        anchors.centerIn: parent
        rowSpacing: spacing
        columnSpacing: spacing

        Repeater {
            id: gridRepeater
            model: parent.boardSize * parent.boardSize
            Field {
                width: minSize/3-10
                height: minSize/3-10

                MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(gameController.clickField(index / gameBoard.boardSize,(gameBoard.boardSize - index % gameBoard.boardSize)-1) == false)
                                {
                                    return
                                }

                                updateView()
                            }
                }
            }
        }
    }

    Button {
        id: exitButton
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom; bottomMargin: 10
        }
        text: "Exit"
        onClicked: { Qt.quit() }
    }

    Button {
        id: actionButton
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: exitButton.top; bottomMargin: 10
        }
        text: "XYZ"
        onClicked: { gameController.actionButton(); updateView(); }
    }


//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//        }
//    }
}
