#ifndef Halberd_Kernal_Dom_Hal_Document_H_
#define Halberd_Kernal_Dom_Hal_Document_H_

#include <base/hal_inct.h>

#include "hal_component.h"
#include "hal_document_head.h"
#include "hal_document_content.h"

namespace kernal
{
    class hal_document final
        : public std::enable_shared_from_this<hal_document> {
    public:
        hal_document();
        virtual ~hal_document();

    public:

    public:
        std::shared_ptr<hal_document_head> doc_head_;
        std::shared_ptr<hal_document_content> doc_content_;
    };
}
#endif//Halberd_Kernal_Dom_Hal_Document_H_
