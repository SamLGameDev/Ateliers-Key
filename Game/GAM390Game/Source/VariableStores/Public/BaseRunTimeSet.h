// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


template <typename T>
class BaseRunTimeSet{


public:
	/// <summary>
	/// Add an Object to the Array
	/// </summary>
	/// <param name="Object"></param>
	UFUNCTION(BlueprintCallable)
	virtual void RegisterObject(T Object);

	/// <summary>
	/// Remove an ObJect From the Array
	/// </summary>
	/// <param name="Object"></param>
	UFUNCTION(BlueprintCallable)
	virtual void DeregisterObject(T Object);

	virtual void Clear();

	UFUNCTION(BlueprintCallable)
	virtual const TArray<T> GetRegisteredObjects() const;

	virtual void RegisterObjects(TArray<T> Set);

protected:

	UPROPERTY(VisibleAnywhere)
	TArray<T> m_RegisteredObjects;


};


template<typename T>
void BaseRunTimeSet<T>::RegisterObject(T Object)
{
	m_RegisteredObjects.Add(Object);
}

template<typename T>
void BaseRunTimeSet<T>::RegisterObjects(TArray<T> Set)
{
	m_RegisteredObjects = Set;
}

template<typename T>
void BaseRunTimeSet<T>::DeregisterObject(T Object)
{
	m_RegisteredObjects.Remove(Object);
}

template<typename T>
const inline TArray<T> BaseRunTimeSet<T>::GetRegisteredObjects() const
{
	return m_RegisteredObjects;
}

template<typename T>
inline void BaseRunTimeSet<T>::Clear() {
	m_RegisteredObjects.Empty();
}
