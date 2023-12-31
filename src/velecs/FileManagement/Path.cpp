/// @file    Path.cpp
/// @author  Matthew Green
/// @date    10/23/2023 20:00:53
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/FileManagement/Path.h"
#include "velecs/FileManagement/File.h"
#include "velecs/FileManagement/Directory.h"

#include "velecs/Core/GameExceptions.h"

#include <filesystem>
#include <algorithm>
#include <string>

#ifdef _WIN32
    // Windows-specific code
#include <windows.h>
#include <codecvt>
#include <locale>

static std::string get_executable_path()
{
    std::vector<wchar_t> buffer(MAX_PATH);
    GetModuleFileNameW(NULL, buffer.data(), static_cast<DWORD>(buffer.size()));
    std::wstring widePath(buffer.data());

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), NULL, 0, NULL, NULL);
    std::string utf8Path(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), &utf8Path[0], size_needed, NULL, NULL);

    return utf8Path;
}
#else
#error "Unsupported platform"
#endif

namespace velecs {

// Public Fields

const std::string Path::GAME_DIR    = Path::GetParentDirPath(get_executable_path());

const std::string Path::ASSETS_DIR  = Combine(GAME_DIR,   "assets");
const std::string Path::SHADERS_DIR = Combine(ASSETS_DIR, "shaders");
const std::string Path::MESHES_DIR  = Combine(ASSETS_DIR, "meshes");

// Public Methods

bool Path::Exists(const std::string& path)
{
    return std::filesystem::exists(path);
}

std::string Path::GetParentDirPath(const std::string& path)
{
    std::filesystem::path fsPath(path);
    if (fsPath.has_parent_path())
    {
        return fsPath.parent_path().string();
    }
    else
    {
        throw PathHasNoParentDirectoryException<Path>(path);
    }
}

std::string Path::GetRootDirPath(const std::string& path)
{
    std::filesystem::path fsPath(path);
    if (fsPath.has_parent_path())
    {
        return fsPath.root_path().string();
    }
    else
    {
        throw PathHasNoParentDirectoryException<Path>(path);
    }
}

std::string Path::GetLastDir(const std::string& path)
{
    std::filesystem::path fsPath(path);
    if (fsPath.has_parent_path())
    {
        if (fsPath.has_filename()) // check if fsPath is a file
        {
            return fsPath.parent_path().filename().string();
        }
        else // assume fsPath is a directory
        {
            return fsPath.filename().string();
        }
    }
    else
    {
        throw PathHasNoParentDirectoryException<Path>(path);
    }
}

bool Path::IsAbsolute(const std::string& path)
{
    std::filesystem::path fsPath{path};

    return fsPath.is_absolute();
}

bool Path::IsRelative(const std::string& path)
{
    std::filesystem::path fsPath{path};

    return fsPath.is_relative();
}

std::string Path::Combine(const std::string& path1, const std::string& path2)
{
    return (std::filesystem::path{path1} / std::filesystem::path{path2}).string();
}

template<typename... Paths>
std::string Path::Combine(const std::string& path1, const std::string& path2, Paths... paths)
{
    return Combine(Combine(path1, path2), paths...);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
