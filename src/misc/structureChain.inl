namespace magma
{
inline StructureChain::StructureChain() noexcept:
    head(nullptr),
    hash(0ull)
{}

inline StructureChain::StructureChain(StructureChain&& other) noexcept:
    head(other.head), hash(other.hash)
{
    other.head = nullptr;
    other.hash = 0ull;
}

template<class StructureType>
inline void StructureChain::linkNode(const StructureType& node) noexcept
{
    static_assert(std::is_trivially_copyable<StructureType>::value,
        "node type is required to be trivially copyable");
    static_assert(sizeof(StructureType) > sizeof(VkBaseOutStructure),
        "node type size mismatch");
    MAGMA_ASSERT(sizeofNode(node.sType) == sizeof(StructureType));
    VkBaseOutStructure *tail = copyNode(reinterpret_cast<const VkBaseOutStructure *>(&node));
    if (tail)
    {
        if (!head)
            head = tail;
        else
            tailNode()->pNext = tail;
        hash = core::hashCombine(hash, core::hashArray(
            (uint8_t *)tail, sizeof(StructureType)));
    }
}

inline VkBaseOutStructure *StructureChain::tailNode() noexcept
{
    for (auto node = head; node; node = node->pNext)
    {
        if (!node->pNext)
            return node;
    }
    return nullptr;
}

inline const VkBaseInStructure *StructureChain::tailNode() const noexcept
{
    for (auto node = head; node; node = node->pNext)
    {
        if (!node->pNext)
            return reinterpret_cast<const VkBaseInStructure *>(node);
    }
    return nullptr;
}

inline size_t StructureChain::getSize() const noexcept
{
    size_t size = 0;
    for (auto node = head; node; node = node->pNext)
        ++size;
    return size;
}

#define MAGMA_SPECIALIZE_STRUCTURE_CHAIN_NODE(StructureType, structureType)\
template<>\
inline StructureType *magma::StructureChain::findNode<StructureType>() noexcept\
{\
    return reinterpret_cast<StructureType *>(getNode(structureType));\
}\
\
template<>\
inline const StructureType *magma::StructureChain::findNode<StructureType>() const noexcept\
{\
    return reinterpret_cast<const StructureType *>(getNode(structureType));\
}
} // namespace magma
