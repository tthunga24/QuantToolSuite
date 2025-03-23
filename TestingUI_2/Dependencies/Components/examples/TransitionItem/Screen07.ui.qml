import QtQuick 2.12


/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick Designer Components.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
import TransitionItem 1.0
import FlowView 1.0
import QtQuick.Controls 2.3

FlowView {
    width: 478
    height: 415
    id: flow
    children: [
        Rectangle {
            z: 10
            color: "red"
            width: 478
            height: 20
            MouseArea {
                anchors.fill: parent
                onClicked: flow.goBack()
            }
        }
    ]

    flowDecisions: [
        DecisionDialog {
            id: dialog
            text: "This is a question?"
            targets: [flowTransition6, flowTransition8]
        }
    ]

    flowTransitions: [
        FlowTransition {
            id: flowTransition
            effect: FlowSlideUpEffect {}
            to: page02
            from: page01
        },
        FlowTransition {
            id: flowTransition1
            effect: FlowSlideRightEffect {}
            to: page04
            from: page01
        },
        FlowTransition {
            id: flowTransition2
            effect: FlowSlideDownEffect {}
            to: page01
            from: page02
        },
        FlowTransition {
            id: flowTransition3
            effect: FlowSlideLeftEffect {}
            to: page01
            from: page04
        },
        FlowTransition {
            id: flowTransition4
            from: page01
            to: page05
        },
        FlowTransition {
            id: flowTransition5
            from: page05
            to: page02
        },
        FlowTransition {
            id: flowTransition6
            to: page06
            from: page02
        },
        FlowTransition {
            id: flowTransition7
            to: page02
            from: page06
        }
    ]

    Page01 {
        id: page01

        FlowActionArea {
            target: flowTransition1
            x: 456
            y: 248
            width: 116
            height: 70
        }

        FlowActionArea {
            target: flowTransition
            x: 264
            y: 248
            width: 112
            height: 76
        }

        FlowActionArea {
            target: flowTransition4
            x: 58
            y: 255
            width: 122
            height: 63
        }
    }

    Page02 {
        id: page02

        FlowActionArea {
            id: area
            target: flowTransition2
            x: 168
            y: 360
            width: 108
            height: 40

            Connections {
                target: parent
                onClicked: area.trigger()
            }
        }

        FlowActionArea {
            target: dialog
            x: 168
            y: 154
            width: 176
            height: 20
        }
    }

    Page04 {
        id: page04

        FlowActionArea {
            target: flowTransition3
            x: 244
            y: 342
            width: 152
            height: 56
        }
    }

    Page06 {
        id: page06

        FlowActionArea {
            target: flowTransition7
            x: 394
            y: 325
            width: 159
            height: 123
        }
    }

    Page05 {
        id: page05

        FlowActionArea {
            target: flowTransition5
            x: 389
            y: 202
            width: 144
            height: 115
        }
    }
}



