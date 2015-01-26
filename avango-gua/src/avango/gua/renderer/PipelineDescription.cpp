#include <avango/gua/renderer/PipelineDescription.hpp>
#include <avango/Base.h>
#include <boost/bind.hpp>
#include <avango/Logger.h>

#include <avango/gua/Types.hpp>

namespace
{
  av::Logger& logger(av::getLogger("av::gua::PipelineDescription"));
}

AV_FC_DEFINE(av::gua::PipelineDescription);

AV_FIELD_DEFINE(av::gua::SFPipelineDescription);
AV_FIELD_DEFINE(av::gua::MFPipelineDescription);

av::gua::PipelineDescription::PipelineDescription(
  std::shared_ptr< ::gua::PipelineDescription> const& guaPipelineDescription)
    : m_guaPipelineDescription(guaPipelineDescription)
{

  AV_FC_ADD_ADAPTOR_FIELD(EnableABuffer,
                      boost::bind(&PipelineDescription::getEnableABufferCB, this, _1),
                      boost::bind(&PipelineDescription::setEnableABufferCB, this, _1));
  AV_FC_ADD_ADAPTOR_FIELD(ABufferSize,
                      boost::bind(&PipelineDescription::getABufferSizeCB, this, _1),
                      boost::bind(&PipelineDescription::setABufferSizeCB, this, _1));
}

void
av::gua::PipelineDescription::initClass()
{
    if (!isTypeInitialized())
    {
        av::FieldContainer::initClass();

        AV_FC_INIT(av::FieldContainer, av::gua::PipelineDescription, true);

        SFPipelineDescription::initClass("av::gua::SFPipelineDescription", "av::Field");
        MFPipelineDescription::initClass("av::gua::MFPipelineDescription", "av::Field");

        // sClassTypeId.setDistributable(true);
    }
}

void
av::gua::PipelineDescription::getEnableABufferCB(const SFBool::GetValueEvent& event)
{
  *(event.getValuePtr()) = m_guaPipelineDescription->get_enable_abuffer();
}

void
av::gua::PipelineDescription::setEnableABufferCB(const SFBool::SetValueEvent& event)
{
  m_guaPipelineDescription->set_enable_abuffer(event.getValue());
}

void
av::gua::PipelineDescription::getABufferSizeCB(const SFInt::GetValueEvent& event)
{
  *(event.getValuePtr()) = m_guaPipelineDescription->get_abuffer_size();
}

void
av::gua::PipelineDescription::setABufferSizeCB(const SFInt::SetValueEvent& event)
{
  m_guaPipelineDescription->set_abuffer_size(event.getValue());
}

av::Link<av::gua::TriMeshPassDescription>
av::gua::PipelineDescription::add_tri_mesh_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::TriMeshPassDescription>());

    auto desc(new av::Link<av::gua::TriMeshPassDescription>(
                        new av::gua::TriMeshPassDescription(
                            std::shared_ptr<::gua::TriMeshPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::TriMeshPassDescription>
av::gua::PipelineDescription::get_tri_mesh_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::TriMeshPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::TriMeshPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::TriMeshPassDescription>(
                        new av::gua::TriMeshPassDescription(
                            std::shared_ptr<::gua::TriMeshPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::TriMeshPassDescription>>
av::gua::PipelineDescription::get_tri_mesh_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::TriMeshPassDescription>());
    std::vector<av::Link<av::gua::TriMeshPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::TriMeshPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::TriMeshPassDescription>(
                        new av::gua::TriMeshPassDescription(
                            std::shared_ptr<::gua::TriMeshPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}

av::Link<av::gua::TexturedQuadPassDescription>
av::gua::PipelineDescription::add_textured_quad_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::TexturedQuadPassDescription>());

    auto desc(new av::Link<av::gua::TexturedQuadPassDescription>(
                        new av::gua::TexturedQuadPassDescription(
                            std::shared_ptr<::gua::TexturedQuadPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::TexturedQuadPassDescription>
av::gua::PipelineDescription::get_textured_quad_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::TexturedQuadPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::TexturedQuadPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::TexturedQuadPassDescription>(
                        new av::gua::TexturedQuadPassDescription(
                            std::shared_ptr<::gua::TexturedQuadPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::TexturedQuadPassDescription>>
av::gua::PipelineDescription::get_textured_quad_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::TexturedQuadPassDescription>());
    std::vector<av::Link<av::gua::TexturedQuadPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::TexturedQuadPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::TexturedQuadPassDescription>(
                        new av::gua::TexturedQuadPassDescription(
                            std::shared_ptr<::gua::TexturedQuadPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}

av::Link<av::gua::BackgroundPassDescription>
av::gua::PipelineDescription::add_background_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::BackgroundPassDescription>());

    auto desc(new av::Link<av::gua::BackgroundPassDescription>(
                        new av::gua::BackgroundPassDescription(
                            std::shared_ptr<::gua::BackgroundPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::BackgroundPassDescription>
av::gua::PipelineDescription::get_background_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::BackgroundPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::BackgroundPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::BackgroundPassDescription>(
                        new av::gua::BackgroundPassDescription(
                            std::shared_ptr<::gua::BackgroundPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::BackgroundPassDescription>>
av::gua::PipelineDescription::get_background_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::BackgroundPassDescription>());
    std::vector<av::Link<av::gua::BackgroundPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::BackgroundPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::BackgroundPassDescription>(
                        new av::gua::BackgroundPassDescription(
                            std::shared_ptr<::gua::BackgroundPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}

av::Link<av::gua::BBoxPassDescription>
av::gua::PipelineDescription::add_bbox_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::BBoxPassDescription>());

    auto desc(new av::Link<av::gua::BBoxPassDescription>(
                        new av::gua::BBoxPassDescription(
                            std::shared_ptr<::gua::BBoxPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::BBoxPassDescription>
av::gua::PipelineDescription::get_bbox_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::BBoxPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::BBoxPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::BBoxPassDescription>(
                        new av::gua::BBoxPassDescription(
                            std::shared_ptr<::gua::BBoxPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::BBoxPassDescription>>
av::gua::PipelineDescription::get_bbox_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::BBoxPassDescription>());
    std::vector<av::Link<av::gua::BBoxPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::BBoxPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::BBoxPassDescription>(
                        new av::gua::BBoxPassDescription(
                            std::shared_ptr<::gua::BBoxPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}


av::Link<av::gua::EmissivePassDescription>
av::gua::PipelineDescription::add_emissive_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::EmissivePassDescription>());

    auto desc(new av::Link<av::gua::EmissivePassDescription>(
                        new av::gua::EmissivePassDescription(
                            std::shared_ptr<::gua::EmissivePassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::EmissivePassDescription>
av::gua::PipelineDescription::get_emissive_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::EmissivePassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::EmissivePassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::EmissivePassDescription>(
                        new av::gua::EmissivePassDescription(
                            std::shared_ptr<::gua::EmissivePassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::EmissivePassDescription>>
av::gua::PipelineDescription::get_emissive_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::EmissivePassDescription>());
    std::vector<av::Link<av::gua::EmissivePassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::EmissivePassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::EmissivePassDescription>(
                        new av::gua::EmissivePassDescription(
                            std::shared_ptr<::gua::EmissivePassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}


av::Link<av::gua::PhysicallyBasedShadingPassDescription>
av::gua::PipelineDescription::add_physically_based_shading_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::PhysicallyBasedShadingPassDescription>());

    auto desc(new av::Link<av::gua::PhysicallyBasedShadingPassDescription>(
                        new av::gua::PhysicallyBasedShadingPassDescription(
                            std::shared_ptr<::gua::PhysicallyBasedShadingPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::PhysicallyBasedShadingPassDescription>
av::gua::PipelineDescription::get_physically_based_shading_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::PhysicallyBasedShadingPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::PhysicallyBasedShadingPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::PhysicallyBasedShadingPassDescription>(
                        new av::gua::PhysicallyBasedShadingPassDescription(
                            std::shared_ptr<::gua::PhysicallyBasedShadingPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::PhysicallyBasedShadingPassDescription>>
av::gua::PipelineDescription::get_physically_based_shading_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::PhysicallyBasedShadingPassDescription>());
    std::vector<av::Link<av::gua::PhysicallyBasedShadingPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::PhysicallyBasedShadingPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::PhysicallyBasedShadingPassDescription>(
                        new av::gua::PhysicallyBasedShadingPassDescription(
                            std::shared_ptr<::gua::PhysicallyBasedShadingPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}


av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>
av::gua::PipelineDescription::add_textured_screen_space_quad_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::TexturedScreenSpaceQuadPassDescription>());

    auto desc(new av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>(
                        new av::gua::TexturedScreenSpaceQuadPassDescription(
                            std::shared_ptr<::gua::TexturedScreenSpaceQuadPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>
av::gua::PipelineDescription::get_textured_screen_space_quad_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::TexturedScreenSpaceQuadPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>(
                        new av::gua::TexturedScreenSpaceQuadPassDescription(
                            std::shared_ptr<::gua::TexturedScreenSpaceQuadPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>>
av::gua::PipelineDescription::get_textured_screen_space_quad_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::TexturedScreenSpaceQuadPassDescription>());
    std::vector<av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::TexturedScreenSpaceQuadPassDescription>(
                        new av::gua::TexturedScreenSpaceQuadPassDescription(
                            std::shared_ptr<::gua::TexturedScreenSpaceQuadPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}


av::Link<av::gua::FullscreenPassDescription>
av::gua::PipelineDescription::add_fullscreen_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::FullscreenPassDescription>());

    auto desc(new av::Link<av::gua::FullscreenPassDescription>(
                        new av::gua::FullscreenPassDescription(
                            std::shared_ptr<::gua::FullscreenPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::FullscreenPassDescription>
av::gua::PipelineDescription::get_fullscreen_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::FullscreenPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::FullscreenPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::FullscreenPassDescription>(
                        new av::gua::FullscreenPassDescription(
                            std::shared_ptr<::gua::FullscreenPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::FullscreenPassDescription>>
av::gua::PipelineDescription::get_fullscreen_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::FullscreenPassDescription>());
    std::vector<av::Link<av::gua::FullscreenPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::FullscreenPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::FullscreenPassDescription>(
                        new av::gua::FullscreenPassDescription(
                            std::shared_ptr<::gua::FullscreenPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}


av::Link<av::gua::SSAOPassDescription>
av::gua::PipelineDescription::add_ssao_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::SSAOPassDescription>());

    auto desc(new av::Link<av::gua::SSAOPassDescription>(
                        new av::gua::SSAOPassDescription(
                            std::shared_ptr<::gua::SSAOPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::SSAOPassDescription>
av::gua::PipelineDescription::get_ssao_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::SSAOPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::SSAOPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::SSAOPassDescription>(
                        new av::gua::SSAOPassDescription(
                            std::shared_ptr<::gua::SSAOPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::SSAOPassDescription>>
av::gua::PipelineDescription::get_ssao_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::SSAOPassDescription>());
    std::vector<av::Link<av::gua::SSAOPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::SSAOPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::SSAOPassDescription>(
                        new av::gua::SSAOPassDescription(
                            std::shared_ptr<::gua::SSAOPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}

av::Link<av::gua::ResolvePassDescription>
av::gua::PipelineDescription::add_resolve_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::ResolvePassDescription>());

    auto desc(new av::Link<av::gua::ResolvePassDescription>(
                        new av::gua::ResolvePassDescription(
                            std::shared_ptr<::gua::ResolvePassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::ResolvePassDescription>
av::gua::PipelineDescription::get_resolve_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::ResolvePassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::ResolvePassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::ResolvePassDescription>(
                        new av::gua::ResolvePassDescription(
                            std::shared_ptr<::gua::ResolvePassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::ResolvePassDescription>>
av::gua::PipelineDescription::get_resolve_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::ResolvePassDescription>());
    std::vector<av::Link<av::gua::ResolvePassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::ResolvePassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::ResolvePassDescription>(
                        new av::gua::ResolvePassDescription(
                            std::shared_ptr<::gua::ResolvePassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}

av::Link<av::gua::LightVisibilityPassDescription>
av::gua::PipelineDescription::add_light_visibility_pass()
{
    auto& pass(m_guaPipelineDescription->add_pass<::gua::LightVisibilityPassDescription>());

    auto desc(new av::Link<av::gua::LightVisibilityPassDescription>(
                        new av::gua::LightVisibilityPassDescription(
                            std::shared_ptr<::gua::LightVisibilityPassDescription>(&pass))));

    pass.set_user_data(desc);

    return *desc;
}

av::Link<av::gua::LightVisibilityPassDescription>
av::gua::PipelineDescription::get_light_visibility_pass()
{
    auto& pass(m_guaPipelineDescription->get_pass<::gua::LightVisibilityPassDescription>());

    if (pass.get_user_data()) {
      auto desc = *static_cast<av::Link<av::gua::LightVisibilityPassDescription>*>(pass.get_user_data());
      return desc;
    } else {
      auto desc(new av::Link<av::gua::LightVisibilityPassDescription>(
                        new av::gua::LightVisibilityPassDescription(
                            std::shared_ptr<::gua::LightVisibilityPassDescription>(&pass))));

      pass.set_user_data(desc);

      return *desc;
    }
}

std::vector<av::Link<av::gua::LightVisibilityPassDescription>>
av::gua::PipelineDescription::get_light_visibility_passes()
{
    auto passes(m_guaPipelineDescription->get_passes<::gua::LightVisibilityPassDescription>());
    std::vector<av::Link<av::gua::LightVisibilityPassDescription>> result;
    for (auto pass : passes) {
      if (pass->get_user_data()) {
        result.push_back(*static_cast<av::Link<av::gua::LightVisibilityPassDescription>*>(pass->get_user_data()));
      } else {
        auto desc(new av::Link<av::gua::LightVisibilityPassDescription>(
                        new av::gua::LightVisibilityPassDescription(
                            std::shared_ptr<::gua::LightVisibilityPassDescription>(pass))));

        pass->set_user_data(desc);
        result.push_back(*desc);
      }
    }

    return result;
}


std::shared_ptr< ::gua::PipelineDescription> const&
av::gua::PipelineDescription::getGuaPipelineDescription() const
{
    return m_guaPipelineDescription;
}


