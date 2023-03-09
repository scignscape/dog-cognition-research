
#ifndef STASH_SIGNALS_ALT_BASE__H
#define STASH_SIGNALS_ALT_BASE__H

#include "stash-signals.h"

#include <QPushButton>
#include <QCheckBox>

#include "subwindows/range-slider.h"


STASH_SIGNALS_ALT_BASE(QPushButton, QAbstractButton)
STASH_SIGNALS_ALT_BASE(QCheckBox, QAbstractButton)

//STASH_SIGNALS_ALT_BASE(ctkRangeSlider, QSlider)
//STASH_SIGNALS_ALT_BASE(QSlider, QAbstractSlider)

STASH_SIGNALS_ALT_BASE(ctkRangeSlider, QAbstractSlider)
//STASH_SIGNALS_ALT_BASE(QSlider, QAbstractSlider)

#endif
