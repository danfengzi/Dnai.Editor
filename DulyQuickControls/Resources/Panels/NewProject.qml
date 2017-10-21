import QtQuick 2.4
import QtQuick.Controls 2.2
import Tools 1.0
import "../Forms"

NewProjectForm {
    property Popup popup

    fileDialog.onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
    }
    fileDialog.onRejected: {
        console.log("Canceled")
    }
    chooseButton.onClicked: fileDialog.open()
    createButton.onClicked: function () {
        if (projectPath.text && projectName.text) {
            Manager.createProject(projectName.text, projectDescription.text, projectPath.text);
            popup.close()
        }
    }
}
