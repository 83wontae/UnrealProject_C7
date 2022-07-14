// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FBlueprintSessionResult;
struct FSessionsSearchSetting;
class UObject;
class APlayerController;
enum class EBPServerPresenceSearchType : uint8;
class UFindSessionsCallbackProxyAdvanced;
#ifdef ADVANCEDSESSIONS_FindSessionsCallbackProxyAdvanced_generated_h
#error "FindSessionsCallbackProxyAdvanced.generated.h already included, missing '#pragma once' in FindSessionsCallbackProxyAdvanced.h"
#endif
#define ADVANCEDSESSIONS_FindSessionsCallbackProxyAdvanced_generated_h

#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_SPARSE_DATA
#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFilterSessionResults); \
	DECLARE_FUNCTION(execFindSessionsAdvanced);


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFilterSessionResults); \
	DECLARE_FUNCTION(execFindSessionsAdvanced);


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFindSessionsCallbackProxyAdvanced(); \
	friend struct Z_Construct_UClass_UFindSessionsCallbackProxyAdvanced_Statics; \
public: \
	DECLARE_CLASS(UFindSessionsCallbackProxyAdvanced, UOnlineBlueprintCallProxyBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSessions"), ADVANCEDSESSIONS_API) \
	DECLARE_SERIALIZER(UFindSessionsCallbackProxyAdvanced)


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_INCLASS \
private: \
	static void StaticRegisterNativesUFindSessionsCallbackProxyAdvanced(); \
	friend struct Z_Construct_UClass_UFindSessionsCallbackProxyAdvanced_Statics; \
public: \
	DECLARE_CLASS(UFindSessionsCallbackProxyAdvanced, UOnlineBlueprintCallProxyBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSessions"), ADVANCEDSESSIONS_API) \
	DECLARE_SERIALIZER(UFindSessionsCallbackProxyAdvanced)


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	ADVANCEDSESSIONS_API UFindSessionsCallbackProxyAdvanced(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFindSessionsCallbackProxyAdvanced) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ADVANCEDSESSIONS_API, UFindSessionsCallbackProxyAdvanced); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFindSessionsCallbackProxyAdvanced); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ADVANCEDSESSIONS_API UFindSessionsCallbackProxyAdvanced(UFindSessionsCallbackProxyAdvanced&&); \
	ADVANCEDSESSIONS_API UFindSessionsCallbackProxyAdvanced(const UFindSessionsCallbackProxyAdvanced&); \
public:


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	ADVANCEDSESSIONS_API UFindSessionsCallbackProxyAdvanced(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ADVANCEDSESSIONS_API UFindSessionsCallbackProxyAdvanced(UFindSessionsCallbackProxyAdvanced&&); \
	ADVANCEDSESSIONS_API UFindSessionsCallbackProxyAdvanced(const UFindSessionsCallbackProxyAdvanced&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ADVANCEDSESSIONS_API, UFindSessionsCallbackProxyAdvanced); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFindSessionsCallbackProxyAdvanced); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFindSessionsCallbackProxyAdvanced)


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_PRIVATE_PROPERTY_OFFSET
#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_10_PROLOG
#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_PRIVATE_PROPERTY_OFFSET \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_SPARSE_DATA \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_RPC_WRAPPERS \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_INCLASS \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_PRIVATE_PROPERTY_OFFSET \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_SPARSE_DATA \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_INCLASS_NO_PURE_DECLS \
	ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h_13_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class FindSessionsCallbackProxyAdvanced."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ADVANCEDSESSIONS_API UClass* StaticClass<class UFindSessionsCallbackProxyAdvanced>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShootingGame_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_FindSessionsCallbackProxyAdvanced_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
