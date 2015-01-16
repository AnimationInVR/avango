#include <avango/gua/renderer/MaterialShaderMethod.hpp>
#include <avango/Base.h>
#include <boost/bind.hpp>
#include <avango/Logger.h>

#include <avango/gua/Types.hpp>

namespace
{
  av::Logger& logger(av::getLogger("av::gua::MaterialShaderMethod"));
}

AV_FC_DEFINE(av::gua::MaterialShaderMethod);

AV_FIELD_DEFINE(av::gua::SFMaterialShaderMethod);
AV_FIELD_DEFINE(av::gua::MFMaterialShaderMethod);

av::gua::MaterialShaderMethod::MaterialShaderMethod(::gua::MaterialShaderMethod const& guaMaterialShaderMethod)
    : m_guaMaterialShaderMethod(guaMaterialShaderMethod)
{

  AV_FC_ADD_ADAPTOR_FIELD(Name,
                      boost::bind(&MaterialShaderMethod::getNameCB, this, _1),
                      boost::bind(&MaterialShaderMethod::setNameCB, this, _1));

  AV_FC_ADD_ADAPTOR_FIELD(Source,
                      boost::bind(&MaterialShaderMethod::getSourceCB, this, _1),
                      boost::bind(&MaterialShaderMethod::setSourceCB, this, _1));
}

void
av::gua::MaterialShaderMethod::initClass()
{
    if (!isTypeInitialized())
    {
        av::FieldContainer::initClass();

        AV_FC_INIT(av::FieldContainer, av::gua::MaterialShaderMethod, true);

        SFMaterialShaderMethod::initClass("av::gua::SFMaterialShaderMethod", "av::Field");
        MFMaterialShaderMethod::initClass("av::gua::MFMaterialShaderMethod", "av::Field");

        sClassTypeId.setDistributable(true);
    }
}

void
av::gua::MaterialShaderMethod::getNameCB(const SFString::GetValueEvent& event)
{
  *(event.getValuePtr()) = m_guaMaterialShaderMethod.get_name();
}

void
av::gua::MaterialShaderMethod::setNameCB(const SFString::SetValueEvent& event)
{
  m_guaMaterialShaderMethod.set_name(event.getValue());
}

void
av::gua::MaterialShaderMethod::getSourceCB(const SFString::GetValueEvent& event)
{
  *(event.getValuePtr()) = m_guaMaterialShaderMethod.get_source();
}

void
av::gua::MaterialShaderMethod::setSourceCB(const SFString::SetValueEvent& event)
{
  m_guaMaterialShaderMethod.set_source(event.getValue());
}

::gua::MaterialShaderMethod const&
av::gua::MaterialShaderMethod::getGuaMaterialShaderMethod() const
{
    return m_guaMaterialShaderMethod;
}


