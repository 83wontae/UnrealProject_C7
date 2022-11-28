// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EBPTextFilteringContext : uint8;
struct FBPUniqueNetId;
struct FBPSteamGroupInfo;
enum class EBlueprintResultSwitch : uint8;
enum class ESteamUserOverlayType : uint8;
enum class EBlueprintAsyncResultSwitch : uint8;
enum class SteamAvatarSize : uint8;
class UTexture2D;
#ifdef ADVANCEDSTEAMSESSIONS_AdvancedSteamFriendsLibrary_generated_h
#error "AdvancedSteamFriendsLibrary.generated.h already included, missing '#pragma once' in AdvancedSteamFriendsLibrary.h"
#endif
#define ADVANCEDSTEAMSESSIONS_AdvancedSteamFriendsLibrary_generated_h

#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_289_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics; \
	ADVANCEDSTEAMSESSIONS_API static class UScriptStruct* StaticStruct();


template<> ADVANCEDSTEAMSESSIONS_API UScriptStruct* StaticStruct<struct FBPSteamGroupInfo>();

#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_SPARSE_DATA
#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execIsSteamInBigPictureMode); \
	DECLARE_FUNCTION(execFilterText); \
	DECLARE_FUNCTION(execInitTextFiltering); \
	DECLARE_FUNCTION(execGetSteamGroups); \
	DECLARE_FUNCTION(execGetSteamFriendGamePlayed); \
	DECLARE_FUNCTION(execGetLocalSteamIDFromSteam); \
	DECLARE_FUNCTION(execCreateSteamIDFromString); \
	DECLARE_FUNCTION(execGetSteamPersonaName); \
	DECLARE_FUNCTION(execGetFriendSteamLevel); \
	DECLARE_FUNCTION(execIsOverlayEnabled); \
	DECLARE_FUNCTION(execOpenSteamUserOverlay); \
	DECLARE_FUNCTION(execRequestSteamFriendInfo); \
	DECLARE_FUNCTION(execGetSteamFriendAvatar);


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execIsSteamInBigPictureMode); \
	DECLARE_FUNCTION(execFilterText); \
	DECLARE_FUNCTION(execInitTextFiltering); \
	DECLARE_FUNCTION(execGetSteamGroups); \
	DECLARE_FUNCTION(execGetSteamFriendGamePlayed); \
	DECLARE_FUNCTION(execGetLocalSteamIDFromSteam); \
	DECLARE_FUNCTION(execCreateSteamIDFromString); \
	DECLARE_FUNCTION(execGetSteamPersonaName); \
	DECLARE_FUNCTION(execGetFriendSteamLevel); \
	DECLARE_FUNCTION(execIsOverlayEnabled); \
	DECLARE_FUNCTION(execOpenSteamUserOverlay); \
	DECLARE_FUNCTION(execRequestSteamFriendInfo); \
	DECLARE_FUNCTION(execGetSteamFriendAvatar);


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAdvancedSteamFriendsLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics; \
public: \
	DECLARE_CLASS(UAdvancedSteamFriendsLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSteamSessions"), NO_API) \
	DECLARE_SERIALIZER(UAdvancedSteamFriendsLibrary)


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_INCLASS \
private: \
	static void StaticRegisterNativesUAdvancedSteamFriendsLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics; \
public: \
	DECLARE_CLASS(UAdvancedSteamFriendsLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSteamSessions"), NO_API) \
	DECLARE_SERIALIZER(UAdvancedSteamFriendsLibrary)


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedSteamFriendsLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedSteamFriendsLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedSteamFriendsLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedSteamFriendsLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAdvancedSteamFriendsLibrary(UAdvancedSteamFriendsLibrary&&); \
	NO_API UAdvancedSteamFriendsLibrary(const UAdvancedSteamFriendsLibrary&); \
public:


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedSteamFriendsLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAdvancedSteamFriendsLibrary(UAdvancedSteamFriendsLibrary&&); \
	NO_API UAdvancedSteamFriendsLibrary(const UAdvancedSteamFriendsLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedSteamFriendsLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedSteamFriendsLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedSteamFriendsLibrary)


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_321_PROLOG
#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_SPARSE_DATA \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_RPC_WRAPPERS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_INCLASS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_SPARSE_DATA \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_324_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ADVANCEDSTEAMSESSIONS_API UClass* StaticClass<class UAdvancedSteamFriendsLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h


#define FOREACH_ENUM_EBPTEXTFILTERINGCONTEXT(op) \
	op(EBPTextFilteringContext::FContext_Unknown) \
	op(EBPTextFilteringContext::FContext_GameContent) \
	op(EBPTextFilteringContext::FContext_Chat) \
	op(EBPTextFilteringContext::FContext_Name) 

enum class EBPTextFilteringContext : uint8;
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<EBPTextFilteringContext>();

#define FOREACH_ENUM_ESTEAMUSEROVERLAYTYPE(op) \
	op(ESteamUserOverlayType::steamid) \
	op(ESteamUserOverlayType::chat) \
	op(ESteamUserOverlayType::jointrade) \
	op(ESteamUserOverlayType::stats) \
	op(ESteamUserOverlayType::achievements) \
	op(ESteamUserOverlayType::friendadd) \
	op(ESteamUserOverlayType::friendremove) \
	op(ESteamUserOverlayType::friendrequestaccept) \
	op(ESteamUserOverlayType::friendrequestignore) 

enum class ESteamUserOverlayType : uint8;
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<ESteamUserOverlayType>();

#define FOREACH_ENUM_STEAMAVATARSIZE(op) \
	op(SteamAvatarSize::SteamAvatar_INVALID) \
	op(SteamAvatarSize::SteamAvatar_Small) \
	op(SteamAvatarSize::SteamAvatar_Medium) \
	op(SteamAvatarSize::SteamAvatar_Large) 

enum class SteamAvatarSize : uint8;
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<SteamAvatarSize>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
