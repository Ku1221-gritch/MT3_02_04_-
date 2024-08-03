#include <Novice.h>
#include "MT3.h"
#include <imgui.h>

const char kWindowTitle[] = "GC2B_07_サトウ_クウ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Triangle triangle;
	triangle.vertices[0] = { -1.0f, 0.0f, 0.0f };
	triangle.vertices[1] = { 0.0f, 1.0f, 0.0f };
	triangle.vertices[2] = { 1.0f, 0.0f, 0.0f };

	Segment segment{ {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} };
	uint32_t color = WHITE;

	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraRotate = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate = { 0.0f, 0.0f, -9.49f };
	Vector3 cameraPosition = { 0,0,-5.0f };

	Vector3 start{};
	Vector3 end{};

	Matrix4x4 viewProjectionMatrix = {};
	Matrix4x4 viewportMatrix = {};
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		viewProjectionMatrix = MakeViewProjectionMatrix({ 1, 1, 1 }, rotate, translate, { 1, 1, 1 }, cameraRotate, cameraTranslate);
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		if (isCollision(triangle, segment)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("triangle.vertices[0]", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("triangle.vertices[1]", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("triangle.vertices[2]", &triangle.vertices[2].x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawSegment(segment, viewProjectionMatrix, viewportMatrix, color);
		DrawTriangle(triangle, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		/// 
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}