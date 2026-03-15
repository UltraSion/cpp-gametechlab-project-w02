#include <windows.h>

#include "Core/Core.h"
#include "Engine/Engine.h"
#include "GUI/GUI.h"
#include "Renderer/Renderer.h"

// 엔진 컴포넌트들 포함
#include "AActor.h"
#include "UCubeComp.h"
#include "UStaticMeshComp.h"
#include "UCameraComponent.h"
#include "USceneComponent.h"

#include "Sphere.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 테스트용 액터 클래스
class ATestCubeActor : public AActor
{
public:
    ATestCubeActor()
    {
        // 루트 컴포넌트 생성
        USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
        SetRootComponent(Root);

        // 큐브 컴포넌트 생성 및 부착
        CubeComp = CreateDefaultSubobject<UCubeComp>("CubeComponent");
        CubeComp->SetupAttachment(Root);

        // 액터 이름 설정
        ActorName = "TestCube";
    }

    UCubeComp* CubeComp = nullptr;
};

class ACameraActor : public AActor
{
public:
    ACameraActor()
    {
        // 루트 컴포넌트로 카메라 컴포넌트 사용
        CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
        SetRootComponent(CameraComp);

        ActorName = "Camera";
    }

    UCameraComponent* CameraComp = nullptr;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    {
        return true;
    }

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WCHAR WindowClass[] = L"JungleWindowClass";
    WCHAR Title[] = L"Actor-Component Test";
    WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

    RegisterClassW(&wndclass);

    HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
        nullptr, nullptr, hInstance, nullptr);

    URenderer renderer;
    renderer.Create(hWnd);
    renderer.CreateShader();
    renderer.CreateConstantBuffer();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplWin32_Init((void*)hWnd);
    ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

    // 액터-컴포넌트 시스템 테스트
    ATestCubeActor* TestCube = new ATestCubeActor();
    ACameraActor* Camera = new ACameraActor();

    // 액터 위치 설정
    TestCube->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
    Camera->SetActorLocation(FVector(0.0f, -5.0f, 0.0f));

    // BeginPlay 호출
    TestCube->BeginPlay();
    Camera->BeginPlay();

    // 기존 구체 렌더링 코드
    UINT numVerticesSphere = sizeof(sphere_vertices) / sizeof(FVertex);
    ID3D11Buffer* vertexBufferSphere = renderer.CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));

    bool bIsExit = false;
    const int targetFPS = 60;
    const double targetFrameTime = 1000.0 / targetFPS;

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    LARGE_INTEGER startTime, endTime;
    double elapsedTime = 0.0;

    // 메인 루프
    while (bIsExit == false)
    {
        QueryPerformanceCounter(&startTime);

        MSG message = {};
        if (PeekMessageW(&message, hWnd, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
            {
                bIsExit = true;
            }
            else
            {
                TranslateMessage(&message);
                DispatchMessageW(&message);
            }
        }

        // 액터 업데이트 (Tick)
        float DeltaTime = (float)(elapsedTime / 1000.0); // 초 단위로 변환
        TestCube->Tick(DeltaTime);
        Camera->Tick(DeltaTime);

        // 렌더링 시작
        renderer.Prepare();
        renderer.PrepareShader();

        // GUI 시작
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 액터-컴포넌트 정보 표시
        ImGui::Begin("Actor-Component Info");
        {
            ImGui::Text("Test Cube Actor:");
            ImGui::Text("  Name: %s", TestCube->GetName().c_str());
            ImGui::Text("  Components: %d", (int)TestCube->OwnedComponents.size());
            FVector CubePos = TestCube->GetActorLocation();
            ImGui::Text("  Position: (%.2f, %.2f, %.2f)", CubePos.x, CubePos.y, CubePos.z);

            ImGui::Separator();

            ImGui::Text("Camera Actor:");
            ImGui::Text("  Name: %s", Camera->GetName().c_str());
            ImGui::Text("  Components: %d", (int)Camera->OwnedComponents.size());
            FVector CamPos = Camera->GetActorLocation();
            ImGui::Text("  Position: (%.2f, %.2f, %.2f)", CamPos.x, CamPos.y, CamPos.z);
        }
        ImGui::End();

        // 액터 컴포넌트 렌더링 (아직 큐브 컴포넌트의 Render가 완전하지 않아서 주석)
        // TestCube->RenderComponents(&renderer);

        // 기존 구체 렌더링
        renderer.UpdateConstant(FVector(0, 0, 0));
        renderer.RenderPrimitive(vertexBufferSphere, numVerticesSphere);

        // GUI 렌더링
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        renderer.SwapBuffer();

        // FPS 제한
        QueryPerformanceCounter(&endTime);
        elapsedTime = ((double)(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart) * 1000.0;

        if (elapsedTime < targetFrameTime)
        {
            Sleep((DWORD)(targetFrameTime - elapsedTime));
        }
    }

    // 정리
    delete TestCube;
    delete Camera;

    renderer.ReleaseVertexBuffer(vertexBufferSphere);
    renderer.ReleaseConstantBuffer();
    renderer.ReleaseShader();
    renderer.Release();

    return 0;
}