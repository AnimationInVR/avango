#include <avango/gua/scenegraph/ClippingPlaneNode.hpp>

#include <avango/gua/Types.hpp>
#include <avango/Base.h>
#include <boost/bind.hpp>

AV_FC_DEFINE(av::gua::ClippingPlaneNode);

AV_FIELD_DEFINE(av::gua::SFClippingPlaneNode);
AV_FIELD_DEFINE(av::gua::MFClippingPlaneNode);

av::gua::ClippingPlaneNode::ClippingPlaneNode(std::shared_ptr< ::gua::node::ClippingPlaneNode> guanode)
    : av::gua::Node(guanode),
      m_guaNode(std::dynamic_pointer_cast< ::gua::node::ClippingPlaneNode>(Node::getGuaNode()))
{}

av::gua::ClippingPlaneNode::~ClippingPlaneNode()
{}

void
av::gua::ClippingPlaneNode::initClass()
{
    if (!isTypeInitialized())
    {
        av::gua::Node::initClass();

        AV_FC_INIT(av::gua::Node, av::gua::ClippingPlaneNode, true);

        SFClippingPlaneNode::initClass("av::gua::SFClippingPlaneNode", "av::Field");
        MFClippingPlaneNode::initClass("av::gua::MFClippingPlaneNode", "av::Field");

        sClassTypeId.setDistributable(true);
    }
}

std::shared_ptr< ::gua::node::ClippingPlaneNode>
av::gua::ClippingPlaneNode::getGuaNode() const
{
    return m_guaNode;
}
