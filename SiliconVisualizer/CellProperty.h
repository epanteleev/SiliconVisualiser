#pragma once
#include <QVector3D>

namespace atom {

    enum class OscilationT {
        acousticTransverse = 0,
        acousticLongitudinal,
        opticalTransverse,
        opticalLongitudinal
    };

    class CellProperty final {
    public:
        CellProperty() = default;

        CellProperty(const CellProperty& cell) {
            this->copy(cell);
        }

        ~CellProperty() = default;

        void copy(const CellProperty& arg) noexcept {
            m_scale = arg.m_scale;
            m_ampl = arg.m_ampl;
            m_q = arg.m_q;
            m_freq = arg.m_freq;
            m_oscilT = arg.m_oscilT;
        }

        inline const CellProperty clone() {
            CellProperty p;
            p.copy(*this);
            return p;
        }

    public:
        QVector3D m_scale;
        double m_ampl = 0.1;
        double m_q = 1.0;
        double m_freq = 1.0;
        OscilationT m_oscilT = OscilationT::acousticLongitudinal;
    };
}
