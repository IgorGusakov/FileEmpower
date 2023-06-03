//
// Created by Igor Gusakov.
//

#ifndef FILEEMPOWER_OUTPUTCRTPVIEWER_H
#define FILEEMPOWER_OUTPUTCRTPVIEWER_H

namespace file_empower {

    template <typename OutputT>
    class OutputCRTPViewer {
    public:
        void accessData()
        {
            static_cast<OutputT*>(this)->draw_data();
        }
    };

}// namespace file_empower

#endif//FILEEMPOWER_OUTPUTCRTPVIEWER_H
