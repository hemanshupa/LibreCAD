/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by 
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/

void QG_DimensionLabelEditor::setLabel(const QString& l) {
    int i0, i1a, i1b, i2;
    QString label, tol1, tol2;
    bool hasDiameter = false;
    
    label = l;
    
    if (label.at(0)==QChar(0x2205) || label.at(0)==QChar(0xF8)) {
        hasDiameter = true;
        bDiameter->setOn(true);
    }
    
    i0 = l.find("\\S");
    if (i0>=0) {
        i1a = l.find("^ ", i0);
        i1b = i1a+1;
        if (i1a<0) {
            i1a = i1b = l.find('^', i0);
        }
        if (i1a>=0) {
            i2 = l.find(';', i1b);
            label = l.mid(0, i0);
            tol1 = l.mid(i0+2, i1a-i0-2);
            tol2 = l.mid(i1b+1, i2-i1b-1);
        }
    }
    
    leLabel->setText(label.mid(hasDiameter));
    leTol1->setText(tol1);
    leTol2->setText(tol2);
}

QString QG_DimensionLabelEditor::getLabel() {
    QString l = leLabel->text();
    
    // diameter:
    if (bDiameter->isOn()) {
        if (l.isEmpty()) {
            l = QString("%1<>").arg(QChar(0x2205));
        }
        else {
            l = QChar(0x2205) + l;
        }
    }
    
    if (leTol1->text().isEmpty() && leTol2->text().isEmpty()) {
        return l;
    }
    else {
        return l + "\\S" + leTol1->text() + 
            "^ " + leTol2->text() + ";";
    }
}

void QG_DimensionLabelEditor::insertSign(const QString& s) {
    leLabel->insert(s.left(1));
}
