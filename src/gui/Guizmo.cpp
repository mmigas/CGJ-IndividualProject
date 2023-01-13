#include "Guizmo.hpp"
#include "../scene/Scene.hpp"
#include <glm/gtx/matrix_decompose.hpp>

bool DecomposeTransform(const glm::mat4 &transform, glm::vec3 &translation, glm::vec3 &rotation, glm::vec3 &scale) {
    // From glm::decompose in matrix_decompose.inl

    using namespace glm;
    using T = float;

    mat4 LocalMatrix(transform);

    // Normalize the matrix.
    if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
        return false;

    // First, isolate perspective.  This is the messiest.
    if (
            epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
            epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
            epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>())) {
        // Clear the perspective partition
        LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
        LocalMatrix[3][3] = static_cast<T>(1);
    }

    // Next take care of translation (easy).
    translation = vec3(LocalMatrix[3]);
    LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

    vec3 Row[3], Pdum3;

    // Now get scale and shear.
    for (length_t i = 0; i < 3; ++i)
        for (length_t j = 0; j < 3; ++j)
            Row[i][j] = LocalMatrix[i][j];

    // Compute X scale factor and normalize first row.
    scale.x = length(Row[0]);
    Row[0] = detail::scale(Row[0], static_cast<T>(1));
    scale.y = length(Row[1]);
    Row[1] = detail::scale(Row[1], static_cast<T>(1));
    scale.z = length(Row[2]);
    Row[2] = detail::scale(Row[2], static_cast<T>(1));

    // At this point, the matrix (in rows[]) is orthonormal.
    // Check for a coordinate system flip.  If the determinant
    // is -1, then negate the matrix and the scaling factors.
#if 0
    Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
        if (dot(Row[0], Pdum3) < 0)
        {
            for (length_t i = 0; i < 3; i++)
            {
                scale[i] *= static_cast<T>(-1);
                Row[i] *= static_cast<T>(-1);
            }
        }
#endif

    rotation.y = asin(-Row[0][2]);
    if (cos(rotation.y) != 0) {
        rotation.x = atan2(Row[1][2], Row[2][2]);
        rotation.z = atan2(Row[0][1], Row[0][0]);
    } else {
        rotation.x = atan2(-Row[2][0], Row[1][1]);
        rotation.z = 0;
    }


    return true;
}

void Guizmo::editTransform(ImGuiContext *context, std::shared_ptr<Object> selectedObject) {
    if (selectedObject == nullptr) {
        return;
    }
    mgl::Camera *camera = Scene::getInstance().getCamera();
    ImGuizmo::SetImGuiContext(context);
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    glm::vec2 m_ViewportBounds[2];
    m_ViewportBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
    m_ViewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};
    ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

    // Camera

    // Runtime camera from entity
    // auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
    // const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
    // const glm::mat4& cameraProjection = camera.GetProjection();
    // glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

    // Editor camera
    const glm::mat4 &cameraProjection = camera->GetProjectionMatrix();
    glm::mat4 cameraView = camera->GetViewMatrix();

    // Entity transform
    glm::mat4 transform = selectedObject->getModelMatrix();

/*
    // Snapping
    bool snap = Input::IsKeyPressed(Key::LeftControl);
    float snapValue = 0.5f; // Snap to 0.5m for translation/scale
    // Snap to 45 degrees for rotation

    if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
        snapValue = 45.0f;


    float snapValues[3] = {snapValue, snapValue, snapValue};
*/
    ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                         (ImGuizmo::OPERATION) ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform),
                         nullptr, /*snap ? snapValues : */nullptr);

    if (ImGuizmo::IsUsing()) {
        glm::vec3 translation, rotation, scale;
        DecomposeTransform(transform, translation, rotation, scale);

/*        glm::vec3 deltaRotation = rotation - selectedObject->Rotation;
        selectedObject->Translation = translation;
        selectedObject->Rotation += deltaRotation;
        selectedObject->Scale = scale;*/
    }


}

